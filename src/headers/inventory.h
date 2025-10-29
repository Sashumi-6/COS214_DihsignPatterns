#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <map>

class GardenComponent;

enum InventoryCategory{
    PLANT,
    CARD,
    CONTAINER,
    SOIL,
    WRAPPER,
};

class Inventory {
    public:
        void addStock(InventoryCategory category, std::string item, int quantity);
        void useItem(InventoryCategory category, std::string item, int quantity);

    private:
        std::map<std::string, int> containers, soil, wrappers, card;
        std::map<std::string, std::map<std::string, int>> map;
        GardenComponent* plants ; //"Head" of the composite , ie. Our whole greenhouse , will be able to call createIterator later
};

#endif