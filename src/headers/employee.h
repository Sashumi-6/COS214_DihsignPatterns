#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "productBuilder.h"
#include "command.h"
#include <string>
#include "order.h"

// Employee & Chain of Command
//The way the system is set up an employee can only handle one command at a time
class Employee {
    public:
        virtual void handleRequest();
        virtual bool canHandle(Command* c);
        void setNext(Employee* next);
        bool isAvailable();
        
        
    protected:
        std::string role;

    private:
        Employee* nextHandler;
        int id;
        std::string name;
        EmployeeState state;

};

enum EmployeeState{
    AVAILABLE,
    BUSY,
    ON_BREAK
};

class Cashier : public Employee {
    public:
        void handleRequest();
        bool canHandle(Command* c);
        Product* constructBasic();
        Product* constructBouquet();
        void addItem(std::string type, std::string name);
        void removeItem(std::string type, std::string name);
        void execute(Command* cmd);
        void fufill();

    private:
        Bob* builder;
        Order* currentOrder;
};

class Manager : public Employee {
    public:
        void handleRequest();
        void handleEscalation();
        bool canHandle(Command* c);

    private:
        int numComplaints;

};

class Caretaker : public Employee {
    public:
        void handleRequest();
        bool canHandle(Command* c);
        void waterPlants();
        void movePlants();
        void execute(Command* c);
        void fulfil();
    private:
        GardenSection* assignedSection;
};

// ==============================
//         EMPLOYEE END
// ==============================

// Factory
class EmployeeFactory {
    protected:
        virtual Employee* createEmployee() = 0;
};

class CashierFactory : public EmployeeFactory {
    public:
        Employee* createEmployee();
};

class ManagerFactory : public EmployeeFactory {
    public:
        Employee* createEmployee();
};

class CaretakerFactory : public EmployeeFactory {
    public:
        Employee* createEmployee();
};

#endif