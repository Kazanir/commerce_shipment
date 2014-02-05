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

  return $data;
}
