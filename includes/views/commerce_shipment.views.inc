<?php

/**
 * Export Commerce Shipments to Views.
 */

/**
 * Implements hook_views_data()
 */
function commerce_shipment_views_data() {
  $data = array();

  $data['commerce_shipment']['table']['group']  = t('Commerce Shipment');

  $data['commerce_shipment']['table']['base'] = array(
    'field' => 'shipment_id',
    'title' => t('Commerce Shipments'),
    'help' => t('Shipments for store orders.'),
    'access query tag' => 'commerce_shipment_access',
  );
  $data['commerce_shipment']['table']['entity type'] = 'commerce_shipment';

  // Expose the Shipment ID.
  $data['commerce_shipment']['shipment_id'] = array(
    'title' => t('Shipment ID'),
    'help' => t('The unique internal identifier of the shipment.'),
    'field' => array(
      'handler' => 'commerce_shipment_handler_field_shipment',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  // Expose the shipment type.
  $data['commerce_shipment']['type'] = array(
    'title' => t('Type'),
    'help' => t('The human-readable name of the type of the shipment.'),
    'field' => array(
      'handler' => 'commerce_shipment_handler_field_shipment_type',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_shipment_handler_filter_shipment_type',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the order ID.
  $data['commerce_shipment']['order_id'] = array(
    'title' => t('Order ID', array(), array('context' => 'a drupal commerce order')),
    'help' => t('The unique internal identifier of the associated order.'),
    'field' => array(
      'handler' => 'commerce_order_handler_field_order',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'commerce_order_handler_argument_order_order_id',
      'name field' => 'order_number',
      'numeric' => TRUE,
      'validate type' => 'order_id',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'field' => 'order_id',
      'label' => t('Order', array(), array('context' => 'a drupal commerce order')),
    ),
  );

  return $data;
}

function commerce_shipment_views_data_alter(&$data) {
  // Describe to Views how 'commerce_product_type' table links to the
  // 'commerce_product' table.
  $data['commerce_product_type']['table']['join']['commerce_product'] = array(
      'left_field' => 'type',
      'field' => 'type',
  );

  // Describe commerce_product_type fields to Views.
  $data['commerce_product_type']['table']['group'] = t('Commerce Product Type');

  // Expose the shippable property.
  $data['commerce_product_type']['shippable'] = array(
    'title' => t('Shippable'),
    'help' => t('Whether or not the product is shippable.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'active-disabled' => array(t('Shippable'), t('Unshippable')),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Shippable'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
}
