#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <map>
#include <stdexcept>

class GardenComponent;

enum class InventoryCategory{
    PLANT,
    CARD,
    CONTAINER,
    SOIL,
    WRAPPER,
};

class Inventory {
    public:
        bool addStock(InventoryCategory category, const std::string& item, int quantity);
        bool useItem(InventoryCategory category, const std::string& item, int quantity);
        bool itemExists(InventoryCategory category, const std::string& item) const;
        int getQuantity(InventoryCategory category, const std::string& item) const;
        explicit Inventory(GardenComponent* plants) ;

    private:
        std::map<std::string, int>& mapForCategory(InventoryCategory category);
        const std::map<std::string, int>& mapForCategory(InventoryCategory category) const;
        std::map<std::string, int> containers, soil, wrappers, cards;
        GardenComponent* plants ; //"Head" of the composite , i.e. Our whole greenhouse , will be able to call createIterator later

};

#endif