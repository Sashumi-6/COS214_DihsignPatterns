#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "command.h"
#include "productBuilder.h"
#include "order.h"

class Order;
enum EmployeeState { AVAILABLE, BUSY, ON_BREAK };

class Employee {
public:
    virtual ~Employee() {}

    // Unified handler for all commands
    void handleRequest(Command* cmd) {
        if (canHandle(cmd)) {
            process(cmd);
        } else if (nextHandler) {
            nextHandler->handleRequest(cmd);
        } else {
            std::cout << "No employee could handle this command.\n";
            //error handling
        }
    }

    virtual bool canHandle(Command* cmd) = 0;
    virtual void process(Command* cmd) = 0;

    void setNext(Employee* next) { nextHandler = next; }
    Employee* getNextHandler() const { return nextHandler; }
    bool isAvailable() const { return state == AVAILABLE; }

protected:
    std::string role;
    EmployeeState state = AVAILABLE;

private:
    Employee* nextHandler = nullptr;
};

// ================== Derived Employees ==================

class Cashier : public Employee {
public:
    bool canHandle(Command* cmd) override;
    void process(Command* cmd) override;

    Product* construct(const ProductRequest& req, GardenComponent* greenhouse);//called from Order
    void addItem(Product* product);
    void removeItem(Product* product);

private:
    Bob* builder;
    Order* order;
};

class Caretaker : public Employee {
public:
    bool canHandle(Command* cmd) override;
    void process(Command* cmd) override;

    void waterPlants();
    void movePlants();
    void performMaintenance(GardenComponent* target, MaintenanceType type);
    void plantNewPlant(Plant* plant);

private:
    GardenSection* assignedSection;
};

class Manager : public Employee {
public:
    bool canHandle(Command* cmd) override;
    void process(Command* cmd) override;

    void handleEscalation();

private:
    int numComplaints = 0;
};

// ================== Employee Factories ==================

class EmployeeFactory {
protected:
    virtual Employee* createEmployee() = 0;
};

class CashierFactory : public EmployeeFactory {
public:
    Employee* createEmployee() override;
};

class ManagerFactory : public EmployeeFactory {
public:
    Employee* createEmployee() override;
};

class CaretakerFactory : public EmployeeFactory {
public:
    Employee* createEmployee() override;
};
