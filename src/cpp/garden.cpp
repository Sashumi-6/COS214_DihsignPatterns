/**
 * @file garden.cpp
 * @brief Implements garden composite section behavior.
 */
#include "../headers/garden.h"
#include "../headers/iterator.h"
#include <algorithm>
#include <stdexcept>

/**
 * @brief Waters all child components in the section.
 */
void GardenSection::waterPlant() {
    for (auto* child : children) {
        if (child != nullptr) {
            child->waterPlant();
        }
    }
}

/**
 * @brief Exposes child components to sunlight.
 */
void GardenSection::exposeToSunlight() {
    for (auto* child : children) {
        if (child != nullptr) {
            child->exposeToSunlight();
        }
    }
}

/**
 * @brief Applies water loss to child components.
 */
void GardenSection::loseWater() {
    for (auto* child : children) {
        if (child != nullptr) {
            child->loseWater();
        }
    }
}

/**
 * @brief Determines if the section contains sellable components.
 */
bool GardenSection::canSell() {
    bool hasChild = false;
    for (auto* child : children) {
        if (child == nullptr) {
            continue;
        }
        hasChild = true;
        if (!child->canSell()) {
            return false;
        }
    }
    return hasChild;
}

/**
 * @brief Invokes growth on all child components.
 */
void GardenSection::grow() {
    for (auto* child : children) {
        if (child != nullptr) {
            child->grow();
        }
    }
}

/**
 * @brief Adds a child component to the section.
 */
void GardenSection::add(GardenComponent* param) {
    if (param == nullptr) {
        throw std::invalid_argument("Cannot add null GardenComponent to GardenSection");
    }
    children.push_back(param);
}

/**
 * @brief Retrieves a child component at the specified index.
 */
GardenComponent* GardenSection::getChild(int param) {
    if (param < 0 || static_cast<std::size_t>(param) >= children.size()) {
        throw std::out_of_range("GardenSection child index out of range");
    }
    return children[static_cast<std::size_t>(param)];
}

/**
 * @brief Provides access to the vector of child components.
 */
std::vector<GardenComponent*> GardenSection::getChildren() const { return children; }

/**
 * @brief Removes a specific child component from the section.
 */
void GardenSection::remove(GardenComponent* param) {
    if (param == nullptr) {
        return;
    }
    const auto it = std::find(children.begin(), children.end(), param);
    if (it != children.end()) {
        children.erase(it);
    }
}

/**
 * @brief Identifies the section as a composite rather than a leaf.
 */
bool GardenSection::isLeaf() const { return false; };

/**
 * @brief Creates an iterator that traverses plants within the section.
 */
Iterator<GardenComponent>* GardenSection::createIterator() { return new PlantOnlyIterator(this); }
