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
    //@todo Add a select list form element.

    //@todo Add a quantity text field form element.
  }
}

/**
 * Calculates the quantity of all line items in all shipments.
 *
 * @return
 *   An array of line items and their shipped quantities, or
 *   an empty array if there is no result set.
 */
function commerce_shipment_get_shipped_line_items($order) {
  // Fetch all of the line items in all shipments in $order.
  $query = db_select('commerce_shipment', 'cs');
  $query->join('field_data_commerce_shipment_line_items', 'li', 'cs.shipment_id = li.entity_id');
  $query->addField('li', 'commerce_shipment_line_items_line_item_id', 'line_item_id');
  $query->addExpression('SUM(commerce_shipment_line_items_qty_shipped)', 'sum_of_shipped');
  $query->groupBy('line_item_id');
  $query->condition('cs.order_id', $order->order_id, '=');

  return $query->execute()->fetchAll();
}
