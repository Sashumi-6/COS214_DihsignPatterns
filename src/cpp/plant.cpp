#include <utility>

#include "../headers/plant.h"
#include <stdexcept>
//planstate->plant = null;
Plant::Plant(std::string  name , const double price , WaterLossStrategy* waterLossStrategy , SunlightStrategy* sunlightStrategy , PlantState* state) : waterLossStrategy(waterLossStrategy) , sunlightStrategy(sunlightStrategy) , location(PlantLocation::INSIDE) , name(std::move(name)) , state(state) , price(price) , waterLevel(1), age(0)  {
    state->setPlant(this); 
}
void Plant::waterPlant(){
    state->handleWaterPlant() ;
    if (waterLevel > 1.0) {
        this->setState(new DeadState(this)) ;
    }
}
void Plant::exposeToSunlight() {
    state->handleExposeToSunlight() ;
}
void Plant::loseWater() {
    state->handleLoseWater();
    if (waterLevel < 0.0) {
        this->setState(new DeadState(this)) ;
    }
};

bool Plant::canSell() { return state->canSell(); }

void Plant::addWater(const double amount) { 
    
    waterLevel += amount; 
    if (waterLevel > 1.0) {
        this->setState(new DeadState(this));
    }
}

void Plant::grow() { 
    this->age += 2;
    state->handleGrow(); 
    if (age > 60) {
        this->setState(new DeadState(this));
    }
}

void Plant::add(GardenComponent* param) { throw std::logic_error("Cannot Add A Child To A Plant"); };
GardenComponent* Plant::getChild(int param) { throw std::logic_error("Plant Has No Children"); }
void Plant::remove(GardenComponent* param) { throw std::logic_error("Plant has No Children To Remove"); };
Iterator<GardenComponent>* Plant::createIterator() { throw std::logic_error("Cannot create Iterator for Plant"); }

void Plant::applyExposeToSunlight() {
    const PlantLocation newLocation = sunlightStrategy->exposeToSun();
    this->location = newLocation;
}

void Plant::applyWaterLoss() {
    const double amount = waterLossStrategy->loseWater();
    this->waterLevel -= amount;
    if (waterLevel < 0.0) {
        this->setState(new DeadState(this));
    }
}

void Plant::setState(PlantState* newState) {
    delete this->state;
    this->state = newState;
}

SunlightPreference Plant::getSunlightPreference() const {
    if (dynamic_cast<LowSunlightStrategy*>(sunlightStrategy)) return SunlightPreference::LOW;
    if (dynamic_cast<MedSunlightStrategy*>(sunlightStrategy)) return SunlightPreference::MEDIUM;
    if (dynamic_cast<HighSunlightStrategy*>(sunlightStrategy)) return SunlightPreference::HIGH;
    return SunlightPreference::UNKNOWN;
}

WaterPreference Plant::getWaterPreference() const {
    if (dynamic_cast<LowWaterLoss*>(waterLossStrategy)) return WaterPreference::LOW;
    if (dynamic_cast<MedWaterLoss*>(waterLossStrategy)) return WaterPreference::MEDIUM;
    if (dynamic_cast<HighWaterLoss*>(waterLossStrategy)) return WaterPreference::HIGH;
    return WaterPreference::UNKNOWN;
}

void Plant::tryGrow() {
    
    if (this->waterLevel >= 0.5 && this->age >= 5) {
        this->grow();
    }
}
double LowWaterLoss::loseWater() {
    return 0.15 ;
}

double Plant:: getPrice(){return price;}


double LowWaterLoss::loseWater() { return kLossAmount; }

double MedWaterLoss::loseWater() { return kLossAmount; }

double HighWaterLoss::loseWater() { return kLossAmount; }

PlantLocation LowSunlightStrategy::exposeToSun() { return PlantLocation::INSIDE; }

PlantLocation MedSunlightStrategy::exposeToSun() { return PlantLocation::GREENHOUSE; }

PlantLocation HighSunlightStrategy::exposeToSun() { return PlantLocation::OUTSIDE; }

PlantState::PlantState() : plant(nullptr) {}

PlantState::PlantState(Plant* plant) : plant(plant) {}

SeedlingState::SeedlingState(Plant* plant) : PlantState(plant) {}

MatureState::MatureState(Plant* plant) : PlantState(plant) {}

DeadState::DeadState(Plant* plant) : PlantState(plant) {}

void PlantState::setPlant(Plant* newPlant) { 
    if(this->plant){
        return;
    }
    this->plant = newPlant; 
}

void SeedlingState::handleExposeToSunlight() {
    if (plant == nullptr) {
        return;
    }
    plant->applyExposeToSunlight();
}

void MatureState::handleExposeToSunlight() {
    if (plant == nullptr) {
        return;
    }
    plant->applyExposeToSunlight();
}

void DeadState::handleExposeToSunlight() {
    // std::cout << "Dead plants cannot be exposed to sunlight." << std::endl;
    }

void SeedlingState::handleLoseWater() {
    if (plant == nullptr) {
        return;
    }
    plant->applyWaterLoss();
}

void MatureState::handleLoseWater() {
    if (plant == nullptr) {
        return;
    }
    plant->applyWaterLoss();
}

void DeadState::handleLoseWater() {}

void SeedlingState::handleGrow() {
    if (plant == nullptr) {
        return;
    }
    // this->plant->age += 0.3;
    plant->setState(new MatureState(plant)) ;
}

void MatureState::handleGrow() {
    if (plant == nullptr) {
        return ;
    }
    plant->setState(new DeadState(plant)) ;
}

void SeedlingState::handleWaterPlant() { plant->addWater(Plant::kWaterDose); }

void MatureState::handleWaterPlant() { plant->addWater(Plant::kWaterDose); }

void DeadState::handleWaterPlant() {}

bool SeedlingState::canSell() { return false; }

bool MatureState::canSell() { return true; }

bool DeadState::canSell() { return false; }
