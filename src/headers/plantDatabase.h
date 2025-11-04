#ifndef PLANTDATABASE_H
#define PLANTDATABASE_H

#include "command.h"  // This will include the enum definitions
// OR forward declare if you don't want the full include:
// enum class SunlightPreference;
// enum class WaterPreference;

struct PlantInfo {
    SunlightPreference sunlight;
    WaterPreference water;
    // ... other members
};

#endif