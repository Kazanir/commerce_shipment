<?php

/**
 * @file
 * The controller for the shipment entity containing the CRUD operations.
 */

/**
 * The controller class for shipment entity containing methods for the entity
 * CRUD operations.
 *
 * Mainly relies on the EntityAPIController class provided by the Entity
 * module, just overrides specific features.
 */
class CommerceShipmentEntityController extends EntityAPIController {
  /**
   * Create a default shipment.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   * @return
   *   An object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'shipment_id' => NULL,
      'order_id' => 0,
      'transaction_id' => 0,
      'profile_id' => 0,
      'type' => '',
      'created' => '',
      'changed' => '',
    );

    return parent::create($values);
  }
}
