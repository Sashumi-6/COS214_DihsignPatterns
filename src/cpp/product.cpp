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
     Inventory.useItem(InventoryCategory::WRAPPER, w, 1);
}




float Bouquet::getPrice() {
    if (bouquet && bouquet->getNext() != nullptr) {
        return price + bouquet->getNext()->getPrice();
    } else {
        return price;
    }
}




Decorator::Decorator(Product* component)
    : Product(component ? component->getPlant() : nullptr, nullptr,
              component ? component->getisMain() : false), component(component) {

    if (component && component->getPlant()) {
        this->soil = component->getSoil();
        this->container = component->getContainer();
        this->card = component->getCard();
        this->wrapping = component->getWrapping();
    } else {
        this->plant = nullptr;
    }
}

// ... rest of product.cpp