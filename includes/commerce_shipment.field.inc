<?php

/**
 * @file
 * Defines a field for managing line items in shipment entities.
 */

/**
 * Implements hook_field_info().
 */
//function commerce_shipment_field_info() {
// @todo Remove this.
//  $fields = array();
//
//  $fields['commerce_shipment_line_item'] = array(
//    'label' => t('Shipment Line Items'),
//    'description' => t('Stores line items contained in a shipment'),
//    'default_widget' => 'commerce_shipment_line_item_widget',
//    'default_formatter' => 'commerce_shipment_line_item_formatter',
//    'settings' => array(),
//    'instance_settings' => array(),
//    'property_type' => 'commerce_shipment_line_item',
//    'property_callbacks' => array('commerce_shipment_property_info_callback'),
//  );
//
//  return $fields;
//}

/**
 * Implements hook_field_widget_info().
 */
function commerce_shipment_field_widget_info() {
  $widgets = array();

  $widgets['commerce_shipment_line_item_widget'] = array(
    'label' => t('Dynamic shipment line items form'),
    'field types' => array('entityreference'),
//    'settings' => array(
//      'key' => array('value'),
//    ),
  );

  return $widgets;
}

/**
 * Implements hook_field_formatter_info().
 */
//function commerce_shipment_field_formatter_info() {
// @todo Remove this.
//  return array(
//    'commerce_shipment_line_item_formatter' => array(
//      'label' => t('Default'),
//      'field types' => array('commerce_shipment_line_item'),
////      'settings' => array(
////        'key' => array('value'),
////      ),
//    ),
//  );
//}

/**
 * Implements hook_field_widget_form().
 */
function commerce_shipment_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  if ($instance['widget']['type'] == 'commerce_shipment_line_item_widget') {
    // If we're editing an order...
    if (isset($element['#entity'])) {
      $available_line_items = commerce_shipment_get_available_line_items($form_state['commerce_order']);
      if (!empty($available_line_items)) {
        // Load the line items.
        $line_items = commerce_line_item_load_multiple(array_keys($available_line_items));
        $options = array();
        foreach ($line_items as $line_item) {
          $options[$line_item->line_item_id] = 'Line Item ' . $line_item->line_item_id . ', ' . $line_item->line_item_label . ', Qty x' . $line_item->quantity;
        }
        $element += array(
          '#type' => 'checkboxes',
          '#options' => $options,
          '#title' => t('Add line items to this shipment'),
          //'#default_value' => $default_values,
        );
      }
    }
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
 * Returns the quantity available to ship of a given line item.
 */
//function commerce_shipment_get_available_quantity($line_item) {
// @todo Remove this.


//  $query->addExpression('SUM(commerce_shipment_line_items_qty_shipped)', 'sum_of_shipped');
//  $query->groupBy('commerce_shipment_line_items_line_item_id');
//
//  $query->condition('li.commerce_shipment_line_items_line_item_id', $line_item->line_item_id, '=');
//
//
//
//    // This line item doesn't appear in any shipments thus the entire quantity
//    // is available.
//    return $line_item->quantity;
//  }
//  else {
//    return $line_item->quantity - reset($results);
//  }
//}


/**
 * @return
 *   An array of available line items for a given order keyed by line item id.
 */
function commerce_shipment_get_available_line_items($order) {
  $query = db_select('field_data_commerce_line_items', 'oli');
  $query->addField('oli', 'commerce_line_items_line_item_id');
  $query->leftJoin('field_data_commerce_shipment_line_items', 'sli', 'oli.commerce_line_items_line_item_id = sli.commerce_shipment_line_items_target_id');
  $query->condition('oli.entity_id', $order->order_id, '=');
  $query->isNull('sli.commerce_shipment_line_items_target_id');

  $results = $query->execute()->fetchAllAssoc('commerce_line_items_line_item_id');

  return $results;
}

/*
 * Form ajax callback: return the shipment line items field elements.
 */
//function commerce_shipment_line_item_select_ajax(&$form, &$form_state) {
// @todo Remove this.
//}

/*
 * Element validate callback: verifies quantity of line items in shipment.
 */
function commerce_shipment_qty_to_ship_validate($element, &$form_state, $form) {
  dpm('stop');
}

/**
 * Callback to alter the property info of commerce_shipment_line_item fields.
 *
 * @see commerce_shipment_field_info().
 */
//function commerce_shipment_property_info_callback(&$info, $entity_type, $field, $instance, $field_type) {
//// @todo Remove this.
//  $property = &$info[$entity_type]['bundles'][$instance['bundle']]['properties'][$field['field_name']];
//
//  $property['type'] = ($field['cardinality'] != 1) ? 'list<commerce_shipment_line_item>' : 'commerce_shipment_line_item';
//
//  $property['getter callback'] = 'entity_metadata_field_verbatim_get';
//  $property['setter callback'] = 'entity_metadata_field_verbatim_set';
//  unset($property['query callback']);
//
//  $property['property info']['line_item_id'] = array(
//    'type' => 'integer',
//    'label' => t('Line Item ID'),
//    'setter callback' => 'entity_property_verbatim_set',
//    'getter callback' => 'entity_property_verbatim_get',
//  );
//  $property['property info']['qty_shipped'] = array(
//    'type' => 'decimal',
//    'label' => t('Quantity Shipped'),
//    'setter callback' => 'entity_property_verbatim_set',
//    'getter callback' => 'entity_property_verbatim_get',
//  );
//}

/**
 * Implements hook_query_TAG_alter().
 *
 * Alters the entityreference query
 */
function commerce_shipment_query_entityreference_alter(QueryAlterableInterface $query) {
  // Need to ensure we're dealing with the appropriate query i.e. the query to
  // get available line items referenced by a shipment.
  dpm('stop');
}

