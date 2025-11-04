#include "../headers/garden.h"
#include "../headers/iterator.h"
#include <algorithm>
#include <stdexcept>

void GardenSection::waterPlant() {
    for (auto* child : children) {
        if (child != nullptr) {
            child->waterPlant();
        }
    }
}

void GardenSection::exposeToSunlight() {
    for (auto* child : children) {
        if (child != nullptr) {
            child->exposeToSunlight();
        }
    }
}

void GardenSection::loseWater() {
    for (auto* child : children) {
        if (child != nullptr) {
            child->loseWater();
        }
    }
}

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

void GardenSection::grow() {
    for (auto* child : children) {
        if (child != nullptr) {
            child->grow();
        }
    }
}

void GardenSection::add(GardenComponent* param) {
    if (param == nullptr) {
        throw std::invalid_argument("Cannot add null GardenComponent to GardenSection");
    }
    children.push_back(param);
}

GardenComponent* GardenSection::getChild(int param) {
    if (param < 0 || static_cast<std::size_t>(param) >= children.size()) {
        throw std::out_of_range("GardenSection child index out of range");
    }
    return children[static_cast<std::size_t>(param)];
}

std::vector<GardenComponent*> GardenSection::getChildren() const { return children; }

void GardenSection::remove(GardenComponent* param) {
    if (param == nullptr) {
        return;
    }
    const auto it = std::find(children.begin(), children.end(), param);
    if (it != children.end()) {
        children.erase(it);
    }
}

bool GardenSection::isLeaf() const { return false; };

Iterator<GardenComponent>* GardenSection::createIterator() { return new PlantOnlyIterator(this); }
