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

  /**
   * Overrides EntityReference_SelectionHandler_Generic::getReferencableEntities().
   */
  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    $options = array();
    $entity_type = $this->field['settings']['target_type'];

    $order = commerce_order_load($this->entity->order_id);
    $results = commerce_shipment_get_available_line_items($order);

    if (!empty($results)) {
      $entities = entity_load($entity_type, array_keys($results));
      foreach ($entities as $entity_id => $entity) {
        list(,, $bundle) = entity_extract_ids($entity_type, $entity);
        $options[$bundle][$entity_id] = check_plain($this->getLabel($entity));
      }
    }

    return $options;
  }
}
