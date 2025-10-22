#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "productBuilder.h"
#include "command.h"

// Employee & Chain of Command
class Employee {
    public:
        Product* construct();
        virtual void handleQuery();
        void executeCommands();
        void addCommand(Command* command);
        void execute(Command* cmd);
        void fufill();

    protected:
        Bob* builder;

    private:
        bool isWorking();
        Employee* successor;
        Command* commands;

};

class Cashier : public Employee {
    public:
        void handleQuery();
};

class Manager : public Employee {
    public:
        void handleQuery();
};

class Caretaker : public Employee {
    public:
        void handleQuery();
};

// ==============================
//         EMPLOYEE END
// ==============================

// Factory
class EmployeeFactory {
    public:
        void anOperation();

    protected:
        virtual Employee* createEmployee() = 0;

    private:
        Employee* employee;
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