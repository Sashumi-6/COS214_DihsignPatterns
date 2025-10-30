#include "../headers/inventory.h"

Inventory::Inventory(GardenComponent *plants) : plants(plants) {}

std::map<std::string, int>& Inventory::mapForCategory(const InventoryCategory category) {
    switch (category) {
        case InventoryCategory::CARD : return cards;
        case InventoryCategory::CONTAINER: return containers;
        case InventoryCategory::SOIL : return soil;
        case InventoryCategory::WRAPPER : return wrappers;
        case InventoryCategory::PLANT : break ;
    }
    throw std::invalid_argument("NO Supporting Inventory Map For Category");
}

const std::map<std::string, int>& Inventory::mapForCategory(const InventoryCategory category) const {
    switch (category) {
        case InventoryCategory::CARD : return cards;
        case InventoryCategory::CONTAINER: return containers;
        case InventoryCategory::SOIL : return soil;
        case InventoryCategory::WRAPPER : return wrappers;
        case InventoryCategory::PLANT : break ;
    }
    throw std::invalid_argument("NO Supporting Inventory Map For Category");
}

bool Inventory::addStock(const InventoryCategory category, const std::string& item, int quantity) {
    if (quantity < 0) {
        return false;
    }
    if (category == InventoryCategory::PLANT) {
        //Todo :: Use plant composite to add plant stock
        return false ;
    }
    auto& map = mapForCategory(category) ;
    map[item] += quantity ;
    return true ;
};


bool Inventory::useItem(const InventoryCategory category, const std::string& item, int quantity) {
    if (quantity < 0) {
        return false;
    }
    if (category == InventoryCategory::PLANT) {
        //Todo :: Use plant composite to remove plant stock
        return false ;
    }
    auto& map = mapForCategory(category) ;
    const auto it = map.find(item) ;
    if (it == map.end()) {
        return false;
    }
    if (quantity > it->second) {
        return false;
    }
    it->second -= quantity ;
    return true ;
};


bool Inventory::itemExists(const InventoryCategory category, const std::string& item) const {
    if (category  == InventoryCategory::PLANT) {
        //TODO :: Use plant composite to check if plant exists
        return false;
    }
    const auto& m = mapForCategory(category);
    return m.find(item) != m.end();
};


int  Inventory::getQuantity(const InventoryCategory category, const std::string& item) const {
    if (category == InventoryCategory::PLANT) {
        //Todo :: Use plant composite to check quantity of plant
    }
    const auto& map = mapForCategory(category);
    const auto it = map.find(item);
    if (it == map.end()) {
        return -1;
    }
    return it->second;
};