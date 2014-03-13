Name: Commerce Shipment
Maintainer: Michael Fuerstnau (michfuer)
Version: 7.x-1.x

*******************************************************************************

OVERVIEW:
Commerce Shipment allows an order to be broken into multiple shipments. It
provides a 'commerce_shipment' entity type and a default 'shipment' bundle.

CRUD actions on shipments occur by editing an existing order, and working with
the Inline Entity Form widget which is part of the commerce_shipments
field that is added to the default order bundle on installation of this module.

When creating or updating a shipment you can only add line items to it that are
available to ship, i.e. line items on that order that do not appear in any
other shipments.

A checkbox is added to the product type edit form specifying whether a product
type is shippable or not. Only shippable items are returned by the default
Unshipped Items View.

*******************************************************************************

INSTALLATION:
Commerce Shipment is composed of two modules:
   commerce_shipment - provides entity definition and base hooks,
   commerce_shipment_fields - provides fields for the default shipment bundle,
                              a shipment ref field on the default order bundle,
                              field cleanup uninstall hook, and the default View
                              'Unshipped Items'.

Both are needed and should be installed.

*******************************************************************************

CREDITS:
1) This project was built by Commerce Guys and sponsored by Idea Den.

*******************************************************************************
