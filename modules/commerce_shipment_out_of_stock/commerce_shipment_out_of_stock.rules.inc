<?php

/**
 * @file
 * Rules integration for the checkout process.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_shipment_out_of_stock_rules_action_info() {
  $actions = array();

  $actions['commerce_shipment_out_of_stock_checkout'] = array(
    'label' => t('Capture checkout amount'),
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
 * Action callback: Captures appropriate funds on checkout, and creates a
 * shipment.
 *
 * The amount captured is the sum of all in-stock (shippable) line items +
 * any non-product line items (e.g. shipping fee). A shipment is created with
 * all in-stock (shippable) items, and we associate the payment transaction with
 * it so there's no chance of double charging.
 */
function commerce_shipment_out_of_stock_checkout($order) {
  dpm('stop');
}
