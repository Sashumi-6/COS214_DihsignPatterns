#include <utility>

#include "../headers/plant.h"
#include <stdexcept>
Plant::Plant(std::string  name , const double price , WaterLossStrategy* waterLossStrategy , SunlightStrategy* sunlightStrategy , PlantState* state) : waterLossStrategy(waterLossStrategy) , sunlightStrategy(sunlightStrategy) , location(PlantLocation::INSIDE) , name(std::move(name)) , state(state) , price(price) , waterLevel(1)  {

}
void Plant::waterPlant(){
    state->handleWaterPlant() ;
}
void Plant::exposeToSunlight() {
    state->handleExposeToSunlight() ;
}
void Plant::loseWater() {
    state->handleLoseWater();
};

bool Plant::canSell() {
    return state->canSell();
}

void Plant::addWater(const double amount) {
    waterLevel += amount;
}


void Plant::grow() {
    state->handleGrow();
}
void Plant::add(GardenComponent* param) {
    throw std::logic_error("Cannot Add A Child To A Plant");
};
GardenComponent* Plant::getChild(int param) {
    throw std::logic_error("Plant Has No Children");
}
void Plant::remove(GardenComponent* param) {
    throw std::logic_error("Plant has No Children To Remove");
};
Iterator<GardenComponent>* Plant::createIterator() {
    throw std::logic_error("Cannot create Iterator for Plant");
}


void Plant::applyExposeToSunlight() {
    const PlantLocation newLocation = sunlightStrategy->exposeToSun() ;
    this->location = newLocation;
}

void Plant::applyWaterLoss() {
    const double amount = waterLossStrategy->loseWater();
    this->waterLevel -= amount;
}

void Plant::setState(PlantState* newState) {
    delete this->state;
    this->state = newState;
}
double LowWaterLoss::loseWater() {
    return 0.1 ;
}

double MedWaterLoss::loseWater() {
    return 0.25 ;
}

double HighWaterLoss::loseWater() {
    return 0.35;
}

PlantLocation LowSunlightStrategy::exposeToSun() {
    return PlantLocation::INSIDE;
}

PlantLocation MedSunlightStrategy::exposeToSun() {
    return PlantLocation::GREENHOUSE;
}

PlantLocation HighSunlightStrategy::exposeToSun() {
    return PlantLocation::OUTSIDE;
}

PlantState::PlantState() : plant(nullptr){

}

PlantState::PlantState(Plant *plant) : plant(plant) {

}

SeedlingState::SeedlingState(Plant *plant) : PlantState(plant){

}

MatureState::MatureState(Plant *plant) : PlantState(plant){

}

DeadState::DeadState(Plant *plant) : PlantState(plant){

}




void PlantState::setPlant(Plant* newPlant) {
    this->plant = newPlant;
}


void SeedlingState::handleExposeToSunlight() {
    if (plant == nullptr) {
        return ;
    }
    plant->applyExposeToSunlight() ;
}

void MatureState::handleExposeToSunlight() {
    if (plant == nullptr) {
        return ;
    }
    plant->applyExposeToSunlight() ;
}

void DeadState::handleExposeToSunlight() {
    }

void SeedlingState::handleLoseWater() {
    if (plant == nullptr) {
        return ;
    }
    plant->applyWaterLoss() ;
}

void MatureState::handleLoseWater() {
    if (plant == nullptr) {
        return ;
    }
    plant->applyWaterLoss() ;
}

void DeadState::handleLoseWater() {
}

void SeedlingState::handleGrow() {
    if (plant == nullptr) {
        return ;
    }
    plant->setState(new MatureState(plant)) ;
}

void MatureState::handleGrow() {

}

void DeadState::handleGrow() {

}

void SeedlingState::handleWaterPlant() {
    plant->addWater(0.35) ;
}

void MatureState::handleWaterPlant() {
    plant->addWater(0.35) ;
}

void DeadState::handleWaterPlant() {

}

bool SeedlingState::canSell() {
    return false;
}

bool MatureState::canSell() {
    return true ;
}

bool DeadState::canSell() {
    return false ;
}

