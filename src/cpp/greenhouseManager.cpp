#include "../headers/greenhouseManager.h"

#include "../headers/garden.h"
#include "../headers/iterator.h"
#include "../headers/plant.h"

#include <stdexcept>
#include <utility> 
#include <vector>

#if __has_include("../headers/plantDatabase.h")
#include "../headers/plantDatabase.h"
#define GREENHOUSE_HAS_PLANT_DATABASE 1
#else
#define GREENHOUSE_HAS_PLANT_DATABASE 0
#endif

GreenHouseManager::GreenHouseManager(GardenSection* rootSection, std::string rootIdentifier)
    : root(rootSection), rootName(std::move(rootIdentifier)) {
    if (root == nullptr) {
        throw std::invalid_argument("GreenHouseManager requires a non-null root section");
    }
    indexSection(rootName, root);
}

GardenSection* GreenHouseManager::getRoot() const { return root; }

GardenSection* GreenHouseManager::addSection(const std::string& sectionName) {
    return addSection(sectionName, rootName);
}

GardenSection* GreenHouseManager::addSection(const std::string& sectionName, const std::string& parentSection) {
    if (sectionName.empty()) {
        throw std::invalid_argument("Section name cannot be empty");
    }
    GardenSection* parent = findSection(parentSection);
    if (parent == nullptr) {
        throw std::invalid_argument("Parent section '" + parentSection + "' does not exist");
    }

    GardenSection* existing = findSection(sectionName);
    if (existing != nullptr) {
        return existing;
    }

    auto* section = new GardenSection();
    parent->add(section);
    indexSection(sectionName, section);
    return section;
}

void GreenHouseManager::addPlant(Plant* plant) {
    if (plant == nullptr) {
        throw std::invalid_argument("Cannot add null plant to greenhouse");
    }

    std::string sectionName = resolveSectionForPlant(plant);
    GardenSection* targetSection = ensureSection(sectionName);
    targetSection->add(plant);
}

Plant* GreenHouseManager::find(const std::string& name) const {
    if (root == nullptr) {
        return nullptr;
    }

    PlantOnlyIterator iterator(root);
    for (GardenComponent* component = iterator.first(); component != nullptr; component = iterator.next()) {
        auto* plant = dynamic_cast<Plant*>(component);
        if (plant != nullptr && plant->getName() == name) {
            return plant;
        }
    }
    return nullptr;
}

Plant* GreenHouseManager::findMature(const std::string& name) const {
    Plant* plant = find(name);
    if (plant != nullptr && plant->isMature()) {
        return plant;
    }
    return nullptr;
}

bool GreenHouseManager::removePlant(Plant* plant) {
    if (plant == nullptr) {
        return false;
    }
    return removePlantFromSection(root, plant);
}

bool GreenHouseManager::removePlant(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    Plant* plant = find(name);
    if (plant == nullptr) {
        return false;
    }
    return removePlant(plant);
}

void GreenHouseManager::clearAllDead() {
    if (root == nullptr) {
        return;
    }
    std::vector<Plant*> deadPlants;
    PlantOnlyIterator iterator(root);
    for (GardenComponent* component = iterator.first(); component != nullptr; component = iterator.next()) {
        auto* plant = dynamic_cast<Plant*>(component);
        if (plant != nullptr && plant->isDead()) {
            deadPlants.push_back(plant);
        }
    }
    for (auto* plant : deadPlants) {
        removePlant(plant);
    }
}

GardenSection* GreenHouseManager::findSection(const std::string& sectionName) const {
    if (sectionName.empty()) {
        return root;
    }
    const auto it = sectionIndex.find(sectionName);
    return it != sectionIndex.end() ? it->second : nullptr;
}

GardenSection* GreenHouseManager::ensureSection(const std::string& sectionName) {
    if (sectionName.empty()) {
        return root;
    }
    GardenSection* section = findSection(sectionName);
    if (section != nullptr) {
        return section;
    }
    auto* newSection = new GardenSection();
    root->add(newSection);
    indexSection(sectionName, newSection);
    return newSection;
}

std::string GreenHouseManager::resolveSectionForPlant(const Plant* plant) const {
    if (plant == nullptr) {
        return {};
    }
#if GREENHOUSE_HAS_PLANT_DATABASE
    const auto& entries = PlantDatabase::getAllPlants();
    const auto it = entries.find(plant->getName());
    if (it != entries.end()) {
        return it->second.section;
    }
#endif
    return {};
}

void GreenHouseManager::indexSection(const std::string& sectionName, GardenSection* section) {
    if (section != nullptr && !sectionName.empty()) {
        sectionIndex[sectionName] = section;
    }
}

bool GreenHouseManager::removePlantFromSection(GardenSection* section, Plant* plant) {
    if (section == nullptr || plant == nullptr) {
        return false;
    }

    const std::vector<GardenComponent*> children = section->getChildren();
    for (GardenComponent* child : children) {
        if (child == plant) {
            section->remove(plant);
            return true;
        }
    }

    for (GardenComponent* child : children) {
        if (child != nullptr && !child->isLeaf()) {
            auto* subsection = dynamic_cast<GardenSection*>(child);
            if (removePlantFromSection(subsection, plant)) {
                return true;
            }
        }
    }
    return false;
}
