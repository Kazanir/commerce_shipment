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
    if (!isset($fields['commerce_shipment_line_items'])) {
      $fields['commerce_shipment_line_items'] = array(
        'type' => 'field',
        'label' => t('Line Items'),
        'formatter' => 'entityreference_label',
        'weight' => -100,
      );
    }
    if (!isset($fields['commerce_shipment_tracking_num'])) {
      $fields['commerce_shipment_tracking_num'] = array(
        'type' => 'field',
        'label' => t('Tracking Number'),
        'formatter' => 'text_default',
        'weight' => -99,
      );
    }
    if (!isset($fields['commerce_shipment_status'])) {
      $fields['commerce_shipment_status'] = array(
        'type' => 'field',
        'label' => t('Status'),
        'formatter' => 'list_default',
        'weight' => -98,
      );
    }
    if (!isset($fields['commerce_shipment_merch_cost'])) {
      $fields['commerce_shipment_merch_cost'] = array(
        'type' => 'field',
        'label' => t('Shipping Cost'),
        'formatter' => 'commerce_price_formatted_amount',
        'weight' => -97,
      );
    }
    return $fields;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    // Add the order_id to our shipment entity for use in retrieving available
    // line items by our override of getReferencableEntities().
    if (!empty($form_state['commerce_order'])) {
      $entity_form['#entity']->order_id = $form_state['commerce_order']->order_id;
    }

    $entity_form = parent::entityForm($entity_form, $form_state);

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
    //@todo Add validation requiring at least one line item in a shipment.
  }
}
