#include "../headers/plantDatabase.h"

static std::map<std::string, PlantInfo> PLANTS = {

    // ----------------- SUCCULENTS -----------------
    { "cactus",           { "succulent", SunlightPreference::HIGH,   WaterPreference::LOW } },
    { "aloe vera",        { "succulent", SunlightPreference::HIGH,   WaterPreference::LOW } },
    { "jade plant",       { "succulent", SunlightPreference::HIGH,   WaterPreference::LOW } },
    { "haworthia",        { "succulent", SunlightPreference::MEDIUM, WaterPreference::LOW } },
    { "echeveria",        { "succulent", SunlightPreference::HIGH,   WaterPreference::LOW } },

    // ----------------- TROPICAL -----------------
    { "monstera",         { "tropical",  SunlightPreference::MEDIUM, WaterPreference::MEDIUM } },
    { "philodendron",     { "tropical",  SunlightPreference::MEDIUM, WaterPreference::MEDIUM } },
    { "pothos",           { "tropical",  SunlightPreference::LOW,    WaterPreference::MEDIUM } },
    { "bird of paradise", { "tropical",  SunlightPreference::HIGH,   WaterPreference::MEDIUM } },
    { "peace lily",       { "tropical",  SunlightPreference::LOW,    WaterPreference::HIGH } },

    // ----------------- HERBS -----------------
    { "basil",            { "herb",      SunlightPreference::HIGH,   WaterPreference::HIGH } },
    { "mint",             { "herb",      SunlightPreference::MEDIUM, WaterPreference::HIGH } },
    { "rosemary",         { "herb",      SunlightPreference::HIGH,   WaterPreference::LOW } },
    { "thyme",            { "herb",      SunlightPreference::HIGH,   WaterPreference::LOW } },
    { "oregano",          { "herb",      SunlightPreference::HIGH,   WaterPreference::LOW } },

    // ----------------- FLOWERING -----------------
    { "rose",             { "flowering", SunlightPreference::HIGH,   WaterPreference::MEDIUM } },
    { "lavender",         { "flowering", SunlightPreference::HIGH,   WaterPreference::LOW } },
    { "orchid",           { "flowering", SunlightPreference::LOW,    WaterPreference::MEDIUM } },
    { "sunflower",        { "flowering", SunlightPreference::HIGH,   WaterPreference::HIGH } },
    { "hydrangea",        { "flowering", SunlightPreference::LOW,    WaterPreference::HIGH } }
};

const std::map<std::string, PlantInfo>& PlantDatabase::getAllPlants() {
    return PLANTS;
}
