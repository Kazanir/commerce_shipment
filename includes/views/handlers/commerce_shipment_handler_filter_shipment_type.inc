<?php

/**
 * Filter by shipment type.
 */
class commerce_shipment_handler_filter_shipment_type extends views_handler_filter_in_operator {
  // Display a list of shipment types in the filter's options.
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Shipment type');
      $this->value_options = commerce_shipment_type_options_list();
    }
  }
}
