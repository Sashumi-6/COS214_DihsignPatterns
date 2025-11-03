#include "plantDatabase.h"

static std::vector<PlantInfo> PLANTS = {
    {"Cactus", SunlightPreference::HIGH, WaterPreference::LOW},
    {"Aloe Vera", SunlightPreference::MEDIUM, WaterPreference::LOW},
    {"Fern", SunlightPreference::LOW, WaterPreference::MEDIUM},
    {"Orchid", SunlightPreference::LOW, WaterPreference::HIGH},
    {"Rose", SunlightPreference::HIGH, WaterPreference::MEDIUM},
    {"Basil", SunlightPreference::MEDIUM, WaterPreference::HIGH},
};

const std::vector<PlantInfo>& PlantDatabase::getAllPlants() {
    return PLANTS;
}
