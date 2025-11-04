#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include "employee.h"
#include "frontDesk.h"
class Customer;

class Simulation {
    public:
        Simulation(int numDays = 1);
        void startSimulation();
        bool addCustomer(Customer* customer);
        bool addEmployee(std::string employeeType);
        void setWeather();
        void addPlant(Plant* plant, GardenSection* gardenSection);

    private:
        std::vector<Customer*> customers;
        EmployeeFactory* employeeMaker;
        FrontDesk* frontDesk;
        int numDays;
};

#endif