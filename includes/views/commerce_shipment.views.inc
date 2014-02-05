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

  return $data;
}
