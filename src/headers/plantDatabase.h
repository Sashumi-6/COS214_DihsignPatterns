#pragma once
#include <vector>
#include <string>
#include <map>
#include "command.h"

enum class SunlightPreference;
enum class WaterPreference;
struct PlantInfo {
    std::string section;
    SunlightPreference sunlight;
    WaterPreference water;
    // ... other members
};

class PlantDatabase {
public:
    static const std::map<std::string , PlantInfo>& getAllPlants();
};

