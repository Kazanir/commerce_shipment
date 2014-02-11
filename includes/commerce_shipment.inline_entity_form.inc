<?php

/**
 * @file
 * Defines the inline entity form controller for Commerce Shipments.
 */

class CommerceShipmentInlineEntityFormController extends EntityInlineEntityFormController {
  /**
   * Overrides EntityInlineEntityFormController::tableFields().
   */
  public function tableFields($bundles) {
    $fields = array();

    // Add base fields.
    if (!isset($fields['commerce_shipment_line_item'])) {
      //@todo Add line items field.
    }
    if (!isset($fields['commerce_shipment_tracking_num'])) {
      $fields['commerce_shipment_tracking_num'] = array(
        'type' => 'field',
        'label' => t('Tracking Number'),
        'formatter' => 'text_default',
        'weight' => -99,
      );
    }
    if (!isset($fields['commerce_shipment_status'])) {
      $fields['commerce_shipment_status'] = array(
        'type' => 'field',
        'label' => t('Status'),
        'formatter' => 'list_default',
        'weight' => -98,
      );
    }
    if (!isset($fields['commerce_shipment_merch_cost'])) {
      $fields['commerce_shipment_merch_cost'] = array(
        'type' => 'field',
        'label' => t('Shipping Cost'),
        'formatter' => 'commerce_price_formatted_amount',
        'weight' => -97,
      );
    }
    return $fields;
  }

  /**
   * Overrides EntityInlineEntityFormController::entityForm().
   */
  public function entityForm($entity_form, &$form_state) {
    $info = entity_get_info($this->entityType);
    $entity = $entity_form['#entity'];

    if (!empty($info['fieldable'])) {
      $langcode = entity_language($this->entityType, $entity);
      field_attach_form($this->entityType, $entity, $entity_form, $form_state, $langcode);
    }

    if (!empty($form_state['commerce_order'])) {
      // Currently the customer shipping profile ref. field only supports a
      // single value so we won't set it here. In the future when orders
      // have multiple shipping addresses we can provide a select list for an
      // admin to determine which address the shipment is going to.
      $order = commerce_order_load($form_state['commerce_order']->order_id);
      $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
      $entity->order_id = $order_wrapper->order_id->value();
    }

    return $entity_form;
  }
}

