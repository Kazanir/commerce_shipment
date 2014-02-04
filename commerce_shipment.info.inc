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
  // Payment transaction reference.
  $properties['transaction'] = array(
    'label' => t("Shipment Payment Transaction"),
    'type' => 'commerce_payment_transaction',
    'description' => t("The payment transaction used for this shipment."),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_shipment entities',
    'required' => TRUE,
    'schema field' => 'transaction_id',
  );

  return $info;
}
