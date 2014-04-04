<?php

/**
 * @file
 * Provides the migration class for commerce_shipmentcommerce_multichannel_site entities.
 */

/**
 * Migration class for commerce_shipment entities.
 */
class CommerceMultichannelMigration_commerce_shipment extends CommerceMultichannelMigrationBase {

  /**
   * {@inheritdoc}
   */
  public function __construct(array $arguments = array()) {
    parent::__construct($arguments + array(
      'entity_type' => 'commerce_shipment',
      'group_name' => 'commerce_multichannel_orders',
    ));
  }

}
