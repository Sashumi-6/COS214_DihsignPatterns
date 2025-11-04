#pragma once
#include <vector>
#include <string>
#include <map>
#include "command.h"

struct PlantInfo {
    std::string section;
    SunlightPreference sunlight;
    WaterPreference water;
};

class PlantDatabase {
public:
    static const std::map<std::string , PlantInfo>& getAllPlants();
};

