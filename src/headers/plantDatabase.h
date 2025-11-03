#pragma once
#include <vector>
#include <string>
#include "command.h"

struct PlantInfo {
    std::string name;
    SunlightPreference sunlight;
    WaterPreference water;
};

class PlantDatabase {
public:
    static const std::vector<PlantInfo>& getAllPlants();
};
