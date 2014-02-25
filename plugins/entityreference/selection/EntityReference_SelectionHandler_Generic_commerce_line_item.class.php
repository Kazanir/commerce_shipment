<?php

/**
 * Handler for line items being referenced by commerce_shipment entities.
 */
class  EntityReference_SelectionHandler_Generic_commerce_line_item extends EntityReference_SelectionHandler_Generic {
  /**
   * Overrides EntityReference_SelectionHandler_Generic::getLabel().
   */
  public function getLabel($entity) {
    $target_type = $this->field['settings']['target_type'];
    return entity_access('view', $target_type, $entity) ? $this->commerce_shipment_line_item_get_label($entity) : t('- Restricted access -');
  }

  /**
   * Returns a more meaningful label for managing line items ref. by shipments.
   */
  public function commerce_shipment_line_item_get_label($entity) {
    return t('@line_item_label, x@qty',array('@line_item_label' => $entity->line_item_label, '@qty' => $entity->quantity));
  }
}
