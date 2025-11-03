#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include "employee.h"
class Customer;

class Simulation {
    public:
        Simulation(int numDays = 1);
        void startSimulation();
        bool addCustomer(Customer* customer);
        bool addEmployee(std::string employeeType);
        void setWeather();
        bool initInventory();
        void addPlants(std::vector<Plant*> plants);

    private:
        std::vector<Customer*> customers;
        EmployeeFactory* employeeMaker;
        int numDays;
};

#endif