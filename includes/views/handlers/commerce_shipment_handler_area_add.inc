<?php

/**
 * Defines a handler area that provides a form to add new shipments.
 */
class commerce_shipment_handler_area_add extends views_handler_area {

  function render($empty = FALSE) {
    // Load an order object for the View if a single order argument is present.
    if (in_array('order_id', array_keys($this->view->argument)) &&
      !in_array('order_id_1', array_keys($this->view->argument)) &&
      !empty($this->view->args[$this->view->argument['order_id']->position])) {

      // Load the specified order.
      $order = commerce_order_load($this->view->args[$this->view->argument['order_id']->position]);
    }
    else {
      // Otherwise indicate a valid order is not present.
      $order = FALSE;
    }

    $options = commerce_shipment_type_options_list();

    if (!empty($options)) {
      if (count($options) > 1) {
        // Only add the shipment bundle select list if bundles other than the
        // default exist.
        $form['shipment_type'] = array(
          '#type' => 'select',
          '#options' => $options,
          '#prefix' => '<div class="add-shipment">',
        );
      }
      $form['add_shipment'] = array(
        '#type' => 'submit',
        '#value' => t('Add shipment'),
        '#suffix' => '</div>',
      );
    }
    else {
      $form['shipments_none'] = array(
        '#markup' => t('No shipment types available to add shipments.'),
      );
    }

    return drupal_render($form);
  }
}
