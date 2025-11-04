/**
 * @file plantDatabase.h
 * @brief Declares the static plant database used for lookup and seeding.
 */
#pragma once
#include <vector>
#include <string>
#include <map>
#include "command.h"

enum class SunlightPreference;
enum class WaterPreference;
/**
 * @brief Stores metadata about a plant entry in the database.
 */
struct PlantInfo {
    std::string section;
    SunlightPreference sunlight;
    WaterPreference water;
    // ... other members
};

/**
 * @brief Static repository of plant information for greenhouse setup.
 */
class PlantDatabase {
public:
    /**
     * @brief Provides access to all registered plant metadata.
     * @return Map keyed by plant name.
     */
    static const std::map<std::string , PlantInfo>& getAllPlants();
};
