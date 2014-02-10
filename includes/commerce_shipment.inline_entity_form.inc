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
    if (!isset($fields['commerce_shipment_line_items'])) {

    }
    if (!isset($fields['commerce_shipment_tracking_num'])) {
      $fields['commerce_shipment_tracking_num'] = array(
        'type' => 'field',
        'label' => t('Tracking Number'),
        //'formatter' => 'commerce_product_reference_title_plain',
        'weight' => -99,
      );
    }
    if (!isset($fields['commerce_shipment_status'])) {

    }
    if (!isset($fields['commerce_shipment_merch_cost'])) {

    }

    // Add base properties.
    if (!isset($fields['profile_id'])) {
      $fields['profile_id'] = array(
        'type' => 'property',
        'label' => t('Shipping Address'),
        'formatter' => 'addressfield_default',
        'weight' => -98,
      );
    }
    if (!isset($fields['transaction_id'])) {

    }
    if (!isset($fields['order_id'])) {

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
      // Get all the shipping profiles for the order owner.
      $query = new EntityFieldQuery();

      $query->entityCondition('entity_type', 'commerce_customer_profile', '=')
            ->entityCondition('bundle', 'shipping', '=')
            ->propertyCondition('uid', $form_state['commerce_order']->uid, '=');
      $results = $query->execute();
      // Set the label for each profile as 'Address 1 . Address 2'
      $options = array();
      if (!empty($results['commerce_customer_profile'])) {
        $profile_entities = entity_load('commerce_customer_profile', array_keys($results['commerce_customer_profile']));
        foreach ($profile_entities as $entity_id => $profile_entity) {
          $profile_wrapper = entity_metadata_wrapper('commerce_customer_profile', $profile_entity);
          $options[$profile_wrapper->profile_id->value()] = t($profile_wrapper->commerce_customer_address->thoroughfare->value() . ", " . $profile_wrapper->commerce_customer_address->premise->value());
        }
      }
      $entity_form['profile_id'] = array(
        '#type' => 'select',
        '#title' => t('Shipping Address'),
        '#default_value' => $entity->profile_id,
        '#options' => $options,
        '#required' => TRUE,
        //'#weight' => $extra_fields['status']['weight'],
      );
    }
    
    return $entity_form;
  }
}

