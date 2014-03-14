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
    $entity_wrapper = entity_metadata_wrapper('commerce_line_item', $entity);
    return t('@product_title x @qty',array('@product_title' => $entity_wrapper->commerce_product->title->value(), '@qty' => $entity->quantity));
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
