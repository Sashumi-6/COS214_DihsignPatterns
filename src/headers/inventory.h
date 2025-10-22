#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <map>

class Inventory {
    public:
        void addStock(std::string category, std::string item, int quantity);
        void useItem(std::string category, std::string item, int quantity);

    private:
        std::map<std::string, int> plants, containers, soil, wrappers, card;
        std::map<std::string, std::map<std::string, int>> map;
};

#endif