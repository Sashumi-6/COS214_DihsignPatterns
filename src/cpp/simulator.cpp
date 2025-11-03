#include "../headers/simulator.h"

Simulation::Simulation(FrontDesk* frontDesk, int numDays) : numDays(numDays), frontDesk(frontDesk) {

}

void Simulation::startSimulation() {
    for (int currDay = 0 ; currDay < numDays ; currDay++) {
        // do stuff??
    }
}

bool Simulation::addCustomer(Customer* customer) {
    customers.push_back(customer);
}

bool Simulation::addEmployee(std::string employeeType) {
    if (employeeType == "Manager") {
        employeeMaker = new ManagerFactory;
    }

    if (employeeType == "Caretaker") {
        employeeMaker = new CaretakerFactory;
    }

    if (employeeType == "Cashier") {
        employeeMaker = new CashierFactory;
    }

    frontDesk->addEmployee(employeeMaker->createEmployee()); // issue!!
    delete employeeMaker; // issue!!
}

void Simulation::setWeather() {
    // what the dog doin
}

void Simulation::addPlant(Plant* plant, GardenSection* gardenSection) {
    frontDesk->addPlant(plant, gardenSection);
}
