<?php

/**
 * @file Includes any rules integration provided by the module.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_shipment_outofstock_default_rules_configuration() {
  $configs = array();

  // A rule used to set the shipment transaction id on checkout complete.
  $configs['rules_set_shipment_transaction_id'] = rules_import(
    '{ "rules_set_shipment_transaction_id" : {
      "LABEL" : "Set shipment transaction id",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "shipment" ],
      "REQUIRES" : [ "rules", "commerce_shipment_outofstock", "commerce_checkout" ],
      "ON" : { "commerce_checkout_complete" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
          "entity" : [ "commerce-order" ],
            "type" : "commerce_order",
            "bundle" : { "value" : { "commerce_order" : "commerce_order" } }
          }
        }
      ],
      "DO" : [
        { "commerce_shipment_outofstock_set_txn_id" : { "commerce_order" : [ "commerce_order" ] } }
      ]
      }
    }'
  );

  return $configs;
}
