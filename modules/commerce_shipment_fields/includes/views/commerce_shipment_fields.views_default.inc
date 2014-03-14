<?php

/**
 * @file
 * Default Views.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_shipment_fields_views_default_views() {
  $views = array();

  /**************** Unshipped Items View for fulfilling orders*************/
  $view = new view();
  $view->name = 'commerce_shipment_unshipped_items';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_line_item';
  $view->human_name = 'Unshipped Items';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Unshipped Items';
  $handler->display->display_options['css_class'] = 'commerce-shipment-unshipped-items-view';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'order_id',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'edit_order' => 'edit_order',
    'order_id' => 'order_id',
    'title' => 'title',
    'sku' => 'sku',
    'quantity' => 'quantity',
  );
  $handler->display->display_options['style_options']['default'] = 'order_id';
  $handler->display->display_options['style_options']['info'] = array(
    'edit_order' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'order_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sku' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'quantity' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: field_data_commerce_shipment_line_items */
  $handler->display->display_options['relationships']['reverse_commerce_shipment_line_items_commerce_shipment']['id'] = 'reverse_commerce_shipment_line_items_commerce_shipment';
  $handler->display->display_options['relationships']['reverse_commerce_shipment_line_items_commerce_shipment']['table'] = 'commerce_line_item';
  $handler->display->display_options['relationships']['reverse_commerce_shipment_line_items_commerce_shipment']['field'] = 'reverse_commerce_shipment_line_items_commerce_shipment';
  $handler->display->display_options['relationships']['reverse_commerce_shipment_line_items_commerce_shipment']['ui_name'] = 'field_data_commerce_shipment_line_items';
  $handler->display->display_options['relationships']['reverse_commerce_shipment_line_items_commerce_shipment']['label'] = 'field_data_commerce_shipment_line_items';
  /* Relationship: commerce_order */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['ui_name'] = 'commerce_order';
  $handler->display->display_options['relationships']['order_id']['label'] = 'commerce_order';
  /* Relationship: commerce_product */
  $handler->display->display_options['relationships']['commerce_product_product_id']['id'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['table'] = 'field_data_commerce_product';
  $handler->display->display_options['relationships']['commerce_product_product_id']['field'] = 'commerce_product_product_id';
  $handler->display->display_options['relationships']['commerce_product_product_id']['ui_name'] = 'commerce_product';
  $handler->display->display_options['relationships']['commerce_product_product_id']['label'] = 'commerce_product';
  /* Field: Commerce Order: Edit link */
  $handler->display->display_options['fields']['edit_order']['id'] = 'edit_order';
  $handler->display->display_options['fields']['edit_order']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['edit_order']['field'] = 'edit_order';
  $handler->display->display_options['fields']['edit_order']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['edit_order']['exclude'] = TRUE;
  /* Field: Commerce Line Item: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['label'] = '';
  $handler->display->display_options['fields']['order_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['order_id']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['order_id']['alter']['text'] = 'Order ID: [order_id]  [edit_order]';
  $handler->display->display_options['fields']['order_id']['element_label_colon'] = FALSE;
  /* Field: Commerce Product: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['fields']['title']['link_to_product'] = 0;
  /* Field: Commerce Product: SKU */
  $handler->display->display_options['fields']['sku']['id'] = 'sku';
  $handler->display->display_options['fields']['sku']['table'] = 'commerce_product';
  $handler->display->display_options['fields']['sku']['field'] = 'sku';
  $handler->display->display_options['fields']['sku']['relationship'] = 'commerce_product_product_id';
  /* Field: Commerce Line Item: Quantity */
  $handler->display->display_options['fields']['quantity']['id'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['quantity']['field'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['precision'] = '0';
  /* Filter criterion: Commerce Shipment: Line Items (commerce_shipment_line_items) */
  $handler->display->display_options['filters']['commerce_shipment_line_items_target_id']['id'] = 'commerce_shipment_line_items_target_id';
  $handler->display->display_options['filters']['commerce_shipment_line_items_target_id']['table'] = 'field_data_commerce_shipment_line_items';
  $handler->display->display_options['filters']['commerce_shipment_line_items_target_id']['field'] = 'commerce_shipment_line_items_target_id';
  $handler->display->display_options['filters']['commerce_shipment_line_items_target_id']['relationship'] = 'reverse_commerce_shipment_line_items_commerce_shipment';
  $handler->display->display_options['filters']['commerce_shipment_line_items_target_id']['operator'] = 'empty';
  /* Filter criterion: Commerce Product Type: Shippable */
  $handler->display->display_options['filters']['shippable']['id'] = 'shippable';
  $handler->display->display_options['filters']['shippable']['table'] = 'commerce_product_type';
  $handler->display->display_options['filters']['shippable']['field'] = 'shippable';
  $handler->display->display_options['filters']['shippable']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['filters']['shippable']['value'] = '1';
  /* Filter criterion: Commerce Order: Order status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_order';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'order_id';
  $handler->display->display_options['filters']['status']['operator'] = 'not in';
  $handler->display->display_options['filters']['status']['value'] = array(
    'cart' => 'cart',
    'checkout_checkout' => 'checkout_checkout',
    'checkout_review' => 'checkout_review',
    'checkout_payment' => 'checkout_payment',
    'checkout_complete' => 'checkout_complete',
  );
  /* Filter criterion: Commerce Product: SKU */
  $handler->display->display_options['filters']['sku']['id'] = 'sku';
  $handler->display->display_options['filters']['sku']['table'] = 'commerce_product';
  $handler->display->display_options['filters']['sku']['field'] = 'sku';
  $handler->display->display_options['filters']['sku']['relationship'] = 'commerce_product_product_id';
  $handler->display->display_options['filters']['sku']['exposed'] = TRUE;
  $handler->display->display_options['filters']['sku']['expose']['operator_id'] = 'sku_op';
  $handler->display->display_options['filters']['sku']['expose']['label'] = 'Product SKU';
  $handler->display->display_options['filters']['sku']['expose']['operator'] = 'sku_op';
  $handler->display->display_options['filters']['sku']['expose']['identifier'] = 'sku';
  $handler->display->display_options['filters']['sku']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/commerce/orders/unshipped-items';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Unshipped Items';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $views[$view->name] = $view;

  /**************** Shipments View for entityref field formatter*************/
  $view = new view();
  $view->name = 'commerce_shipment_table';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_shipment';
  $view->human_name = 'Shipments';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'shipment_id' => 'shipment_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'shipment_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Commerce Shipment: Shipment ID */
  $handler->display->display_options['fields']['shipment_id']['id'] = 'shipment_id';
  $handler->display->display_options['fields']['shipment_id']['table'] = 'commerce_shipment';
  $handler->display->display_options['fields']['shipment_id']['field'] = 'shipment_id';
  /* Field: Commerce Shipment: Line Items */
  $handler->display->display_options['fields']['commerce_shipment_line_items']['id'] = 'commerce_shipment_line_items';
  $handler->display->display_options['fields']['commerce_shipment_line_items']['table'] = 'field_data_commerce_shipment_line_items';
  $handler->display->display_options['fields']['commerce_shipment_line_items']['field'] = 'commerce_shipment_line_items';
  $handler->display->display_options['fields']['commerce_shipment_line_items']['label'] = 'Items';
  $handler->display->display_options['fields']['commerce_shipment_line_items']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['commerce_shipment_line_items']['delta_offset'] = '0';
  /* Field: Commerce Shipment: Status */
  $handler->display->display_options['fields']['commerce_shipment_status']['id'] = 'commerce_shipment_status';
  $handler->display->display_options['fields']['commerce_shipment_status']['table'] = 'field_data_commerce_shipment_status';
  $handler->display->display_options['fields']['commerce_shipment_status']['field'] = 'commerce_shipment_status';
  /* Field: Commerce Shipment: Tracking Number */
  $handler->display->display_options['fields']['commerce_shipment_tracking_num']['id'] = 'commerce_shipment_tracking_num';
  $handler->display->display_options['fields']['commerce_shipment_tracking_num']['table'] = 'field_data_commerce_shipment_tracking_num';
  $handler->display->display_options['fields']['commerce_shipment_tracking_num']['field'] = 'commerce_shipment_tracking_num';
  /* Contextual filter: Commerce Shipment: Shipment ID */
  $handler->display->display_options['arguments']['shipment_id']['id'] = 'shipment_id';
  $handler->display->display_options['arguments']['shipment_id']['table'] = 'commerce_shipment';
  $handler->display->display_options['arguments']['shipment_id']['field'] = 'shipment_id';
  $handler->display->display_options['arguments']['shipment_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['shipment_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['shipment_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['shipment_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['shipment_id']['break_phrase'] = TRUE;

  $views[$view->name] = $view;

  return $views;
}
