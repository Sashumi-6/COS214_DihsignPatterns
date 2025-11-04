#pragma once
#include <vector>
#include <string>
#include "command.h"

enum class SunlightPreference;
enum class WaterPreference;
struct PlantInfo {
    std::string name;
    SunlightPreference sunlight;
    WaterPreference water;
};

class PlantDatabase {
public:
    static const std::vector<PlantInfo>& getAllPlants();
};
