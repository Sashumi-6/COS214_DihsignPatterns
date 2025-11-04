/**
 * @file inventory.h
 * @brief Declares the inventory subsystem tracking greenhouse supplies.
 *
 * Provides an @ref Inventory facade that manages granular categories used for
 * building customer orders and fulfilling plant care requirements.
 */
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

/**
 * @brief Central store managing counts of greenhouse supplies by category.
 */
class Inventory {
    public:
        /**
         * @brief Adds stock to the desired category.
         * @param category Inventory bucket to update.
         * @param item Descriptive key for the stock line.
         * @param quantity Number of units to increase.
         * @return True if the addition succeeded.
         */
        bool addStock(InventoryCategory category, const std::string& item, int quantity);
        /**
         * @brief Consumes stock items when fulfilling requests.
         * @param category Inventory bucket to update.
         * @param item Item identifier to reduce stock for.
         * @param quantity Units requested.
         * @return True when the requested quantity was available and deducted.
         */
        bool useItem(InventoryCategory category, const std::string& item, int quantity);
        /**
         * @brief Checks if a specific inventory item is tracked.
         * @param category Inventory bucket to search.
         * @param item Item identifier to locate.
         * @return True if the item exists within the category.
         */
        bool itemExists(InventoryCategory category, const std::string& item) const;
        /**
         * @brief Returns remaining quantity for an inventory item.
         * @param category Inventory bucket to inspect.
         * @param item Item identifier to inspect.
         * @return Current quantity, or zero when absent.
         */
        int getQuantity(InventoryCategory category, const std::string& item) const;
        /**
         * @brief Binds the inventory to the greenhouse composite for lookups.
         * @param plants Root component of the greenhouse composite.
         */
        explicit Inventory(GardenComponent* plants) ;

    private:
        /**
         * @brief Retrieves a modifiable reference to the map for a category.
         * @throws std::out_of_range When the category is invalid.
         */
        std::map<std::string, int>& mapForCategory(InventoryCategory category);
        /**
         * @brief Retrieves a read-only reference to the map for a category.
         * @throws std::out_of_range When the category is invalid.
         */
        const std::map<std::string, int>& mapForCategory(InventoryCategory category) const;
        /** Container inventory keyed by item name. */
        std::map<std::string, int> containers, soil, wrappers, cards;
        /**
         * @brief Head of the greenhouse composite for iterating plant stock.
         */
        GardenComponent* plants ; //"Head" of the composite , i.e. Our whole greenhouse , will be able to call createIterator later

};

#endif
