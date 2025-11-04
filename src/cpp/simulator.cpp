#include "../headers/simulator.h"

Simulation::Simulation(int numDays)
    : customers(),
      employeeMaker(nullptr),
      frontDesk(nullptr),
      numDays(numDays) {
    // grab some vector of customers or something
    // then we will for each customer
    // addCustomer()
    // initInventory();

    // grab vector of plants and then init the plants
    // addPlants()
}

void Simulation::startSimulation() {
    for (int currDay = 0 ; currDay < numDays ; currDay++) {

    }
}

bool Simulation::addCustomer(Customer* customer) {
    if (customer == nullptr) {
        return false;
    }
    customers.push_back(customer);
    return true;
}

bool Simulation::addEmployee(std::string employeeType) {
    return !employeeType.empty();
}

void Simulation::setWeather() {
    // what the dog doin
}

void Simulation::addPlant(Plant* plant, GardenSection* gardenSection) {
    if (gardenSection == nullptr || plant == nullptr) {
        return;
    }
    gardenSection->add(plant);
}

// bool Simulation::initInventory() {
//     // init the inventory
// }

// void Simulation::addPlants(std::vector<Plant*> plants) {

// }
