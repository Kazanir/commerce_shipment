<?php

/**
 * @file
 * Defines a field for managing line items in shipment entities.
 */

/**
 * Implements hook_field_info().
 */
function commerce_shipment_field_info() {
  $fields = array();

  $fields['commerce_shipment_line_item'] = array(
    'label' => t('Shipment Line Items'),
    'description' => t('Stores line items contained in a shipment'),
    'default_widget' => 'commerce_shipment_line_item_widget',
    'default_formatter' => 'commerce_shipment_line_item_formatter',
  );

  return $fields;
}

/**
 * Implements hook_field_widget_info().
 */
function commerce_shipment_field_widget_info() {
  $widgets = array();

  $widgets['commerce_shipment_line_item_widget'] = array(
    'label' => t('Dynamic line item form'),
    'field types' => array('commerce_shipment_line_item'),
//    'settings' => array(
//      'key' => array('value'),
//    ),
  );

  return $widgets;
}

/**
 * Implements hook_field_formatter_info().
 */
function commerce_shipment_field_formatter_info() {
  return array(
    'commerce_shipment_line_item_formatter' => array(
      'label' => t('Default'),
      'field types' => array('commerce_shipment_line_item'),
//      'settings' => array(
//        'key' => array('value'),
//      ),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function commerce_shipment_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  //@todo Add validation to qty field to not allow quantity <= 0, i.e. they can't add a line item of <= 0 quantity to a shipment.
  if ($instance['widget']['type'] == 'commerce_shipment_line_item_widget') {
    // If we're editing an order...
    if (isset($element['#entity'])) {
      $available_line_items = commerce_shipment_get_available_line_items($form_state['commerce_order']);
      if (!empty($available_line_items)) {
        // Build the select list's options array keyed by line item ID.
        $options = array();
        foreach ($available_line_items as $info) {
          $options[$info['line_item_id']] = $info['line_item_label'];
        }
        $element['line_item_id'] = array(
          '#type' => 'select',
          '#title' => t('Line Item to Ship'),
          '#options' => $options,
          '#weight' => -99,
//        '#default_value' => $category['selected'],
//        '#description' => t('Set this to <em>Yes</em> if you would like this category to be selected by default.'),
        );
      }
    }
    //@todo Add a quantity text field form element.
  }
  return $element;
}

/**
 * Implements hook_field_widget_form_alter().
 */
function commerce_shipment_field_widget_form_alter(&$element, &$form_state, $context) {
  // We need to disable the 'Add new shipment' behavior of IEF for the
  // commerce_shipments field if there are no line items available to ship. Act
  // on widgets for commerce_shipments instances on order entities.
  if ($context['field']['field_name'] == 'commerce_shipments' && $context['instance']['entity_type'] == 'commerce_order') {
    $available_line_items = commerce_shipment_get_available_line_items($context['form']['#entity']);
    if (empty($available_line_items)) {
      $element['actions']['ief_add']['#disabled'] = TRUE;
      $element['actions']['ief_add']['#value'] = t('No line items available to ship');
    }
  }
}

/**
 * Calculates the quantity of available (unshipped) line items in an order.
 *
 * @return
 *   An array of line item id's and their available quantities, or
 *   an empty array if there is no result set.
 */
function commerce_shipment_get_available_line_items($order) {
  // Fetch all of the line items in all shipments in $order.
  $query = db_select('commerce_shipment', 'cs');
  $query->join('field_data_commerce_shipment_line_items', 'li', 'cs.shipment_id = li.entity_id');
  $query->addField('li', 'commerce_shipment_line_items_line_item_id', 'line_item_id');
  $query->addExpression('SUM(commerce_shipment_line_items_qty_shipped)', 'sum_of_shipped');
  $query->groupBy('line_item_id');
  $query->condition('cs.order_id', $order->order_id, '=');

  $results  = $query->execute()->fetchAll();

  $available = array();
  if (!empty($results)){
    $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
    foreach ($order_wrapper->commerce_line_items as $line_item) {
      $found = FALSE;
      foreach ($results as $shipped_line_item) {
        if ($shipped_line_item->line_item_id != $line_item->line_item_id->value()) {
          continue;
        }
        $found = TRUE;
        $quantity_available = $line_item->quantity->value() - $shipped_line_item->sum_of_shipped;
        if ($quantity_available > 0) {
          $available[] = array(
            'line_item_id' => $line_item->line_item_id->value(),
            'qty_available' => $quantity_available,
            'line_item_label' =>$line_item->line_item_label->value(),
          );
        }
      }

      if (!$found) {
        // The line item doesn't appear in any shipments. Add full quantity to
        // the available list.
        $available[] = array(
          'line_item_id' => $line_item->line_item_id->value(),
          'qty_available' => $line_item->quantity->value(),
          'line_item_label' =>$line_item->line_item_label->value(),
        );
      }
    }
  }

  return $available;
}
