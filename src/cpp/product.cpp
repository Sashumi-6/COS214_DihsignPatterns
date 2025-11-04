#include "../headers/productBuilder.h"
#include <stdexcept>
#include <cstdlib> // for rand

// ... rest of your product.cpp code, but update the setter methods:

void Product::setSoil(const std::string& s) {
    soil = s;
    inventory.useItem(InventoryCategory::SOIL, s, 1);  // lowercase 'inventory'
}

void Product::setContainer(const std::string& c) {
    container = c;
    inventory.useItem(InventoryCategory::CONTAINER, c, 1);  // lowercase 'inventory'
}

void Product::setCard(const std::string& c) {
    card = c;
    inventory.useItem(InventoryCategory::CARD, c, 1);  // lowercase 'inventory'
}

void Product::setWrapping(const std::string& w) {
    wrapping = w;
    inventory.useItem(InventoryCategory::WRAPPER, w, 1);  // lowercase 'inventory'
}

// ... rest of product.cpp