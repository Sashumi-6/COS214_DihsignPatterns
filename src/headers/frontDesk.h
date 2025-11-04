#ifndef FRONTDESK_H
#define FRONTDESK_H

#include <string>
#include <vector>
#include "command.h"
#include "employee.h"
#include "productRequest.h"

class Plant;
class GardenSection;
class GardenComponent;
class Order;
class Customer;
class Cashier;
class Caretaker;

class FrontDesk {
public:
    void query();
    void plant();
    void maintain();
    void addCommand(Command* cmd);
    void addEmployee(Employee* emp);
    void addPlant(Plant* plant, GardenSection* section);
    void executeAllCommands();

    template <typename T>
    T* getAvailableEmployee();

    void pay();
    bool placeOrder(std::vector<ProductRequest>& reqs, Customer* c);

private:
    std::vector<Employee*> employees;
    Employee* activeEmployee = nullptr;
    std::vector<Command*> commands;
    Order* currentOrder = nullptr;
    GardenComponent* greenhouse = nullptr;
};

template <typename T>
T* FrontDesk::getAvailableEmployee() {
    for (Employee* e : employees) {
        if (e && e->isAvailable()) {
            if (T* casted = dynamic_cast<T*>(e)) {
                return casted;
            }
        }
    }
    return nullptr;
}

#endif
