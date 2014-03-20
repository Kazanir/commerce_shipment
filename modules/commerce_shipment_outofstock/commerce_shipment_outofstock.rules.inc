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

  $actions['commerce_shipment_outofstock_checkout'] = array(
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
function commerce_shipment_outofstock_checkout($order) {
  // If everything was successful up to this point, then we expect to see a
  // pending (i.e. auth only) payment transaction, for this order for the amount
  // of the order total.
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'commerce_payment_transaction');
  $query->propertyCondition('order_id', $order_wrapper->order_id->value());
  $query->propertyCondition('status', 'pending');
  $query->propertyCondition('amount', $order_wrapper->commerce_order_total->amount->value());

  $results = $query->execute();

  if (!empty($results['commerce_payment_transaction'])) {
    $ids = array_keys($results['commerce_payment_transaction']);
    $payment_txn = commerce_payment_transaction_load(reset($ids));
    dpm($payment_txn);

  }


}
