<?php

/**
 * @file
 * Forms for creating/editing and deleting shipment entities.
 */

/**
 * Form callback: create or edit a shipment.
 *
 * @param $entity
 *   The entity object to edit through the form.
 */
function commerce_shipment_form($form, &$form_state, $entity, $op, $entity_type) {

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_shipment') . '/includes/commerce_shipment.forms.inc';

  // Add the field related form elements.
  $langcode = entity_language('commerce_shipment', $entity);
  if (empty($langcode)) {
    $langcode = LANGUAGE_NONE;
  }

  field_attach_form('commerce_shipment', $entity, $form, $form_state, $langcode);

  // Additional entity properties


  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'a drupal commerce shipment')),
    '#submit' => array_merge($submit, array('commerce_shipment_form_submit')),
    '#weight' => 40,
  );

  $item = menu_get_item('admin/commerce/orders/%commerce_order/shipments');
  if (!empty($item) && $item['access']) {
    $form['actions']['submit']['#suffix'] = l(t('Cancel'), 'admin/commerce/orders/%commerce_order/shipments');
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'commerce_shipment_form_validate';

  return $form;
}


