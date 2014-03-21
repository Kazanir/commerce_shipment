<?php

/**
 * @file
 * Rules integration for the checkout process.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_shipment_outofstock_rules_action_info() {
  $actions = array();

  $actions['commerce_shipment_outofstock_capture_shipment'] = array(
    'label' => t('Capture shipment charge'),
    'parameter' => array(
      'commerce_shipment' => array(
        'type' => 'commerce_shipment',
        'label' => t('New Shipment'),
      ),
    ),
    'group' => t('Commerce Shipment'),
  );

  return $actions;
}

/**
 * Action callback: Attempts to auth+capture against all line items in shipment.
 *
 *
 */
function commerce_shipment_outofstock_capture_shipment($shipment) {
  // Look for a default cof for the order owner. If there is none, log it in
  // watchdog, set a message, and abort.
  return;
  // Calculate the charge to be applied.

  // If for some odd reason charge is greater than order balance, set the charge
  // to be the order balance.
}
