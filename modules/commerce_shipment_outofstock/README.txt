Name: Commerce Shipment Out of Stock
Maintainer: Michael Fuerstnau (michfuer)
Version: 7.x-1.x

*******************************************************************************

OVERVIEW:
This is an extension to the Commerce Shipment module that provides a method for
merchants to sell out of stock products. A potential use case is if you sell
pre-order items with the requirement that customers cannot be charged for those
items at checkout.

It uses Rules to capture the appropriate amount of funds after checkout (i.e.
all in stock, shippable items, and non-product type items (e.g. shipping fee).

The module is payment gateway agnostic, but merchants should set the default
transaction type of the gateways they offer to "Authorization only". This allows
the module to subsequently capture the correct amount on checkout complete.

*******************************************************************************

INSTALLATION:
@todo Fill this out.
