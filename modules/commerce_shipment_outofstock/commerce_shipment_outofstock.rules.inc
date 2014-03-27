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

  $actions['commerce_shipment_outofstock_set_txn_id'] = array(
    'label' => t('Set shipment transaction id'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order in checkout'),
      ),
    ),
    'group' => t('Commerce Shipment'),
  );

  return $actions;
}

/**
 * Action callback: Associates a payment transaction with a shipment.
 *
 * Useful only for Completing checkout events.
 */
function commerce_shipment_outofstock_set_txn_id($order) {
  if (!empty($order->commerce_shipments)) {
    $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
    // We expect only one shipment at most to be created during checkout.
    $shipment = $order_wrapper->commerce_shipments->value();
    $shipment_wrapper = entity_metadata_wrapper('commerce_shipment', reset($shipment));
    $results = commerce_shipment_find_txn_id($order->order_id);

    if (!empty($results)) {
      // Set the payment transaction id for the shipment.
      $shipment_wrapper->transaction_id = reset($results)->transaction_id;
      $shipment_wrapper->save();
    }
  }
}
