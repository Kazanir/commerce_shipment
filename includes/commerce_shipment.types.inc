<?php

/**
 * @file
 */


/**
 * Menu callback: display an overview of available shipment types.
 */
function commerce_shipment_types_overview() {
  drupal_add_css(drupal_get_path('module', 'commerce_shipment') . '/theme/commerce_shipment.admin.css');

  $header = array(
    t('Name'),
    t('Operations'),
  );

  $rows = array();

  // Loop through all defined shipment types.
  foreach (commerce_shipment_types() as $type => $shipment_type) {
    // Build the operation links for the current shipment type.
    $links = menu_contextual_links('commerce-shipment-type', 'admin/commerce/config/shipments', array(commerce_shipment_type_to_arg($type)));

    // Add the shipment type's row to the table's rows array.
    $type_markup = check_plain($shipment_type['name']);
    $type_markup .= ' <small>' . t('(Machine name: @type)', array('@type' => $shipment_type['type'])) . '</small>';
    $type_markup .= '<div class="description">' . filter_xss_admin($shipment_type['description']) . '</div>';

    $rows[] = array(
      $type_markup,
      theme('links', array('links' => $links, 'attributes' => array('class' => 'links inline operations'))),
    );
  }

  // If no shipment types are defined...
  if (empty($rows)) {
    // Add a standard empty row with a link to add a new shipment type.
    $rows[] = array(
      array(
        'data' => t('There are no shipment types.'),
        'colspan' => 2,
      )
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}
