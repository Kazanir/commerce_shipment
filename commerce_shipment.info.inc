<?php

/**
 * @file
 * Provides metadata for the shipment entity.
 */

/**
 * Implements hook_entity_property_info().
 */
function commerce_shipment_entity_property_info() {
  $info = array();

  // Add meta-data about the basic properties.
  $properties = &$info['commerce_shipment']['properties'];

  $properties['shipment_id'] = array(
    'label' => t('Shipment ID'),
    'description' => t('The internal numeric ID of the shipment.'),
    'type' => 'integer',
    'schema field' => 'shipment_id',
  );
  $properties['order_id'] = array(
    'label' => t('Order ID', array(), array('context' => 'a drupal commerce order')),
    'type' => 'integer',
    'description' => t('The unique ID of the order the shipment belongs to.'),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_shipment entities',
    'clear' => array('order'),
    'schema field' => 'order_id',
  );
  // Payment transaction reference.
  $properties['transaction_id'] = array(
    'label' => t("Shipment Payment Transaction"),
    'type' => 'commerce_payment_transaction',
    'description' => t("The unique ID of the payment transaction used for the shipment."),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_shipment entities',
    'required' => TRUE,
    'schema field' => 'transaction_id',
  );
  // Customer Shipping Profile reference.
  $properties['profile_id'] = array(
    'label' => t("Shipment Shipping Profile"),
    'type' => 'commerce_customer_profile',
    'description' => t("The unique ID of the shipping profile used for the shipment."),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_shipment entities',
    'required' => TRUE,
    'schema field' => 'profile_id',
  );
  $properties['type'] = array(
    'label' => t('Type'),
    'description' => t('The type of the shipment.'),
    'type' => 'token',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_shipment entities',
    'options list' => 'commerce_shipment_type_options_list',
    'required' => TRUE,
    'schema field' => 'type',
  );
  $properties['created'] = array(
    'label' => t('Date created'),
    'description' => t('The date the shipment was created.'),
    'type' => 'date',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_shipment entities',
    'schema field' => 'created',
  );
  $properties['changed'] = array(
    'label' => t('Date updated'),
    'description' => t('The date the shipment was most recently updated.'),
    'type' => 'date',
    'setter callback' => 'entity_property_verbatim_set',
    'query callback' => 'entity_metadata_table_query',
    'setter permission' => 'administer commerce_shipment entities',
    'schema field' => 'changed',
  );

  return $info;
}
