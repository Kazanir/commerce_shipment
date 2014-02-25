<?php

$plugin = array(
  'title' => t('Commerce Shipment Entity Ref Handler'),
  'description' => t('Provides specific handling of line items that are being referenced by commerce_shipment entities.'),
  'class' => 'EntityReference_SelectionHandler_Generic_commerce_line_item',
  'behavior type' => 'instance',
);
