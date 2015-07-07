<?php

/**
 * @file
 * Views definitions and data alterations for Commerce Shipment Fields.
 */


/**
 * Implements hook_views_data_alter().
 */
function commerce_shipment_fields_views_data_alter(&$data) {
  // Add a field to the order table to format tracking links.
  $data['commerce_order']['tracking_numbers'] = array(
    'title' => t('Tracking numbers'),
    'help' => t('Formatted tracking numbers that link to carrier sites.'),
    'field' => array(
      'handler' => 'commerce_shipment_fields_handler_field_tracking_numbers',
      'click sortable' => FALSE,
    ),
  );
}
