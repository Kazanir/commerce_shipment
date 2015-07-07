<?php

/**
 * Field handler to format an order's tracking numbers as links.
 */
class commerce_shipment_fields_handler_field_tracking_numbers extends views_handler_field {
  /**
   * Overrides views_handler_field::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_carriers'] = array('default' => array());
    return $options;
  }

  /**
   * Overrides views_handler_field::options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Add a checkboxes list to link known tracking numbers to the related
    // tracking pages on their carriers' sites.
    $form['link_to_carriers'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Link tracking numbers for these carriers to their tracking pages:'),
      '#description' => t('If a carrier is not shown, it is not currently supported by the Commerce Shipment Fields module.'),
      '#options' => commerce_shipment_known_tracking_carriers(),
      '#default_value' => $this->options['link_to_carriers'],
    );
  }

  /**
   * Overrides views_handler_field::query().
   */
  function query() {
    // Include lines from the parent method that do not automatically this field
    // to the query field list since it doesn't actually correspond to a column
    // in the order table.
    $this->ensure_my_table();
    $this->add_additional_fields(array('order_id'));
  }

  /**
   * Overrides views_handler_field::render().
   */
  function render($values) {
    // Initialize an array to hold tracking numbers. This array will be
    // populated with field values from shipments referenced by the current
    // result row's order object.
    $tracking_numbers = array();

    // Load the order represented by the current result row.
    $order = commerce_order_load($this->get_value($values, 'order_id'));

    // If the order could be loaded...
    if (!empty($order)) {
      // Loop over the shipments on the order to extract their tracking numbers.
      $order_wrapper = entity_metadata_wrapper('commerce_order', $order);

      try {
        foreach ($order_wrapper->commerce_shipments as $delta => $shipment_wrapper) {
          $tracking_numbers[] = $shipment_wrapper->commerce_shipment_tracking_num->value();
        }
      }
      catch (Exception $e) {
        watchdog('commerce_shipment_fields', 'The entity metadata wrapper could not traverse the reference from an order to its shipments in commerce_shipment_fields_handler_field_tracking_numbers::render().', array(), WATCHDOG_WARNING);
      }
    }

    // If we found any tracking numbers for the current order, render them into
    // a list with links to the appropriate tracking service where possible.
    foreach ($tracking_numbers as $key => $tracking_number) {
      $carrier = commerce_shipment_get_tracking_number_carrier($tracking_number);

      if (in_array($carrier, array_values($this->options['link_to_carriers']))) {
        // Convert the tracking number into a link to the service.
        $tracking_numbers[$key] = l(check_plain($tracking_number), commerce_shipment_tracking_url($carrier, $tracking_number), array('attributes' => array('target' => '_blank')));
      }
    }

    // Return an unordered list of tracking numbers if multiple were found or
    // a single tracking number if there was only one.
    if (count($tracking_numbers) > 1) {
      return theme('item_list', array('items' => $tracking_numbers, 'attributes' => array('class' => array('tracking-number'))));
    }
    elseif (count($tracking_numbers) == 1) {
      $tracking_number = reset($tracking_numbers);
      return '<div class="tracking-number">' . $tracking_number . '</div>';
    }

    // @todo Figure out how to support token replacement here.
    if (empty($this->options['hide_empty'])) {
      return filter_xss_admin($this->options['empty']);
    }
  }
}
