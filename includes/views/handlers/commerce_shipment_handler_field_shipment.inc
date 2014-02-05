<?php

/**
 * @file
 * Contains the basic shipment field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a shipment.
 */
class commerce_shipment_handler_field_shipment extends views_handler_field {
  function init(&$view, &$options) {
    parent::init($view, $options);

    if (!empty($this->options['link_to_entity'])) {
      $this->additional_fields['shipment_id'] = 'shipment_id';
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['link_to_entity'] = array('default' => FALSE);

    return $options;
  }

  /**
   * Provide the link to entity option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_to_entity'] = array(
      '#title' => t("Link this field to the shipment's administrative view page"),
      '#description' => t('This will override any other link you have set.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_entity']),
    );
  }

  /**
   * Render whatever the data is as a link to the entity.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_entity']) && $data !== NULL && $data !== '') {
      $shipment_id = $this->get_value($values, 'shipment_id');
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = 'admin/commerce/orders/%commerce_order/shipments/manage' . $shipment_id;
    }

    return $data;
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }
}
