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

  return $data;
}
