<?php

/**
 * @file
 * Defines the inline entity form controller for Commerce Shipments.
 */

class CommerceShipmentInlineEntityFormController extends EntityInlineEntityFormController {
  /**
   * Overrides EntityInlineEntityFormController::tableFields().
   */
  public function tableFields($bundles) {
    $fields = array();

    // Add base fields.
    $fields['commerce_shipment_line_items'] = array(
      'type' => 'field',
      'label' => t('Line Items'),
      'formatter' => 'entityreference_label',
      'weight' => -100,
    );
    $fields['commerce_shipment_tracking_num'] = array(
      'type' => 'field',
      'label' => t('Tracking Number'),
      'formatter' => 'text_default',
      'weight' => -99,
    );
    $fields['commerce_shipment_status'] = array(
      'type' => 'field',
      'label' => t('Status'),
      'formatter' => 'list_default',
      'weight' => -98,
    );
    $fields['commerce_shipment_merch_cost'] = array(
      'type' => 'field',
      'label' => t('Shipping Cost'),
      'formatter' => 'commerce_price_formatted_amount',
      'weight' => -97,
    );
    $fields['transaction_id'] = array(
      'type' => 'property',
      'label' => t('Payment'),
      //'formatter' => 'commerce_price_formatted_amount',
      'weight' => -96,
    );
    return $fields;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    $shipment = $entity_form['#entity'];
    // Add the order_id to our shipment entity for use in retrieving available
    // line items by our override of getReferencableEntities().
    if (!empty($form_state['commerce_order'])) {
      $entity_form['#entity']->order_id = $form_state['commerce_order']->order_id;
    }

    $entity_form = parent::entityForm($entity_form, $form_state);

    if (!isset($shipment->transaction_id)) {
      // Check to see if there are any charge methods available for this shipment.
      $charge_options = array();
      // First look for any available payment transactions.
      $conditions = array(
        'order_id' => $shipment->order_id,
      );
      $transactions = commerce_payment_transaction_load_multiple(array(), $conditions);
      // Add a fieldset to group commerce_shipment_txn_list if it exists.
      $entity_form['commerce_shipment_charge'] = array(
        '#type' => 'fieldset'
      );
      if (!empty($transactions)) {
        $charge_options[COMMERCE_SHIPMENT_ASSOC_CHARGE] = t('Associate with an existing charge');
        // Build our select list of possible payment transactions. Currently
        // we don't have any filter criteria, since it's possible that one
        // payment transaction applies to two shipments.
        $list_options = array();
        foreach ($transactions as $transaction) {
          $list_options[$transaction->transaction_id] = $transaction->payment_method . ', ' . commerce_currency_amount_to_decimal($transaction->amount, $transaction->currency_code);
        }
        $parents = $entity_form['#parents'];
        $first_name = array_shift($parents);
        $children = implode('][', $parents);
        $name = $first_name . '[' . $children . '][commerce_shipment_charge][select]';
        $entity_form['commerce_shipment_charge']['commerce_shipment_txn_list'] = array(
          '#type' => 'select',
          '#options' => $list_options,
          '#states' => array(
            'visible' => array(
              ':input[name="' . $name . '"]' => array('value' => COMMERCE_SHIPMENT_ASSOC_CHARGE),
            ),
          ),
          '#weight' => 100,
        );
      }

      // Now check for card on file option.
      $order = commerce_order_load($shipment->order_id);
      $balance = commerce_payment_order_balance($order);
      if (module_exists('commerce_cardonfile') && module_exists('commerce_shipment_outofstock')
          && $balance['amount'] > 0) {
        $charge_options[COMMERCE_SHIPMENT_NEW_CHARGE] = t('Create a new charge using the order owner\'s default card on file');
      }

      if (!empty($charge_options)) {
        $charge_options[COMMERCE_SHIPMENT_NO_CHARGE] = t('Do not charge');

        $entity_form['commerce_shipment_charge']['select'] = array(
          '#type' => 'radios',
          '#title' => t('Shipment charge method'),
          '#options' => array_reverse($charge_options),
          '#default_value' => COMMERCE_SHIPMENT_NO_CHARGE,
        );
      }
      else {
        $entity_form['commerce_shipment_charge'] = array(
          '#type' => 'item',
          '#title' => t('Shipment charge method'),
          '#markup' => t('No shipment charge options available! You need to install commerce_cardonfile and/or add a payment transaction to the order.'),
        );
      }
    }

    // Adjust the weights of the form elements we're adding so that line item
    // selection is at the top.
    $top_weight = $entity_form['commerce_shipment_line_items']['#weight'];
    foreach (array_diff(element_children($entity_form), array('commerce_shipment_line_items')) as $field_name) {
      $entity_form[$field_name]['#weight'] = $top_weight++;
    }

    return $entity_form;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormValidate().
   */
  public function entityFormValidate($entity_form, &$form_state) {
    $shipment = $entity_form['#entity'];
    $parents_path = implode('][', $entity_form['#parents']);
    $line_items = drupal_array_get_nested_value($form_state['values'], $entity_form['commerce_shipment_line_items']['#parents']);
    $lang = $entity_form['commerce_shipment_line_items']['#language'];
    $item = reset($line_items[$lang]);

    if ($shipment->is_new) {
      if (!isset($item['target_id'])) {
        form_set_error($parents_path . '][commerce_shipment_line_items', t('You must add a line item to the shipment'));
      }
    }
    else {
      // The shipment is being updated. Add existing line items to
      // $form_state['values'].
      $shipment_wrapper = entity_metadata_wrapper('commerce_shipment', $shipment);
      foreach ($shipment_wrapper->commerce_shipment_line_items as $line_item_wrapper) {
        $line_items[$lang][]['target_id'] = $line_item_wrapper->line_item_id->value();
      }
      drupal_array_set_nested_value($form_state['values'], $entity_form['commerce_shipment_line_items']['#parents'], $line_items);
    }
  }

  /**
   * Overrides EntityInlineEntityFormController::entityFormSubmit().
   */
  public function entityFormSubmit(&$entity_form, &$form_state) {
    parent::entityFormSubmit($entity_form, $form_state);

    $charge = drupal_array_get_nested_value($form_state['values'], $entity_form['commerce_shipment_charge']['#parents']);
    switch ($charge['select']) {
      case COMMERCE_SHIPMENT_ASSOC_CHARGE:
        // Set the payment transaction id for the shipment.
        $entity_form['#entity']->transaction_id = $charge['commerce_shipment_txn_list'];
        break;
      case COMMERCE_SHIPMENT_NEW_CHARGE:
        $shipment = $entity_form['#entity'];
        // Attempt to charge the order owner's default card on file.
        commerce_shipment_outofstock_capture_shipment($shipment);
        // If a transaction was created it will be the most recent one for this
        // order that is not associated with any other shipments.
        $results = commerce_shipment_find_txn_id($form_state['commerce_order']->order_id);

        if (!empty($results)) {
          // Set the payment transaction id for the shipment.
          $shipment->transaction_id = reset($results)->transaction_id;
          // Make sure the shipment gets saved.
          entity_save('commerce_shipment', $shipment);
          // Add the shipment to the order.
          $order = commerce_order_load($form_state['commerce_order']->order_id);
          $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
          $order_wrapper->commerce_shipments[] = $shipment;
          $order_wrapper->save();
        }
        break;
    }
    drupal_set_message(t('Shipments on this order will not be saved until the <em>Save order</em> button is clicked.'), 'warning');
  }
}
