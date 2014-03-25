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
      'order_id' => NULL,
      'transaction_id' => NULL,
      'profile_id' => NULL,
      'type' => '',
      'created' => '',
      'changed' => '',
    );

    return parent::create($values);
  }

  /**
   * Saves a shipment.
   *
   * @param $entity
   *   The full entity object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    // Hardcode the changed time.
    $entity->changed = REQUEST_TIME;

    if (empty($entity->{$this->idKey}) || !empty($entity->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($entity->created)) {
        $entity->created = REQUEST_TIME;
      }
    }
    else {
      // Otherwise if the entity is not new but comes from an entity_create()
      // or similar function call that initializes the created timestamp and uid
      // value to empty strings, unset them to prevent destroying existing data
      // in those properties on update.
      if ($entity->created === '') {
        unset($entity->created);
      }
    }

    // Determine if we will be inserting a new entity.
    $entity->is_new = empty($entity->{$this->idKey});

    return parent::save($entity, $transaction);
  }
}
