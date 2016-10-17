<?php

/**
 * @file
 * Checkout pane callback functions for the shipment auto module.
 */


/**
 * Checkout pane callback: returns the customer profile pane's settings form.
 */
function commerce_shipment_auto_pane_settings_form($checkout_pane) {
  $form = array();

  ctools_include('plugins');
  $plugins = ctools_get_plugins('commerce_shipment_auto', 'shipment_auto');
  $form['#title'] = t('Automatic Shipment Plugins');
  $form['#description'] = t('Set options for each available choice of shipment-splitting method for your store\'s customers.');

  $form['commerce_shipment_auto_settings'] = array(
    '#type' => 'item',
    '#tree' => TRUE,
  );
  $con = &$form['commerce_shipment_auto_settings'];

  $settings = variable_get('commerce_shipment_auto_settings', commerce_shipment_auto_default_plugin_settings($plugins));

  $states = function($key, $p) {
    return array(
      'disabled' => array(
        ':input[name="commerce_shipment_auto_settings[' . $key . '][enabled]"]' => array('checked' => FALSE),
      ),
    );
  };

  foreach ($plugins as $p) {
    $key = $p['module'] . '_' . $p['name'];
    $con[$key] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#title' => $p['title'],
      '#description' => '<p>Check to enable this shipment-splitting method. If desired, enter a custom description (displayed at checkout) for this shipment-splitting method. Leave blank to use the default description.</p>',    );
    $con[$key]['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => 'Enable',
      '#default_value' => $settings[$key]['enabled'],
    );
    $con[$key]['desc'] = array(
      '#type' => 'textfield',
      '#length' => 255,
      '#width' => 120,
      '#disabled' => FALSE,
      '#default_value' => $settings[$key]['desc'],
      '#states' => $states($key, $p),
      '#description' => 'Default if left blank: <em>' . $p['original_description'] . '</em>',

    );
  }

  return $form;
}

/**
 * Checkout pane callback: returns a customer profile edit form.
 */
function commerce_shipment_auto_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  $pane_form = array('#parents' => array($checkout_pane['pane_id']));

  // Find the referenced profile using the related reference field...
  $wrapper = entity_metadata_wrapper('commerce_order', $order);

  // @TODO: Load all enabled ctools plugins for auto-splitting a cart into shipments.




  return $pane_form;
}

/**
 * Checkout pane callback: validates a customer profile edit form.
 */
function commerce_shipment_auto_pane_checkout_form_validate($form, &$form_state, $checkout_pane, $order) {
  // @TODO: Figureo out which auto-shipment plugin was chosen and validate the choice.

  return TRUE;
}

/**
 * Checkout pane callback: submits a customer profile edit form.
 */
function commerce_shipment_auto_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
  // @TODO: Figure out which auto-shipment plugin was chosen.


  // @TODO: Use it to split the shipments.


  // @TODO: Save the shipments.

}

/**
 * Checkout pane callback: returns the cart contents review data for the
 *   Review checkout pane.
 */
function commerce_shipment_auto_profile_pane_review($form, $form_state, $checkout_pane, $order) {
  // @TODO: Describe which of the various shipment-splitting options, if any,
  // the customer had picked during checkout.
}

