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
 */
function commerce_shipment_outofstock_capture_shipment($shipment) {
  // Look for a default cof for the order owner. If there is none, log it in
  // watchdog, set a message, and abort.
  $order = commerce_order_load($shipment->order_id);
  $response = commerce_cardonfile_order_select_card($order);
  $message_vars = array(
    '@order_id' => $order->order_id,
    '@uid' => $order->uid,
  );
  if ($response['code'] != COMMERCE_COF_PROCESS_CODE_CARD_OK) {
    if (isset($response['card_chosen'])) {
      // It's an expired card. Add the card_id to our message.
      $message_vars['@card_id'] = $response['card_chosen']->card_id;
    }
    watchdog('commerce_shipment_outofstock', $response['message'], $message_vars);
    drupal_set_message(t($response['message'], $message_vars), 'warning');
    return;
  }
  // Calculate the charge to be applied.

  // If for some odd reason charge is greater than order balance, set the charge
  // to be the order balance.
}
