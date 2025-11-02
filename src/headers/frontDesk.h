#ifndef FRONTDESK_H
#define FRONTDESK_H

#include <vector>

#include "employee.h"
#include "command.h"
#include "order.h"

class FrontDesk {
    public:
        void query();
        void plant();
        void maintain();    // bool or void?
        bool addCommand(Command* cmd);
        void addEmployee();
        bool addPlant(Plant* plant, std::string section);
        // void checkSpecials(Customer* customer);
        bool executeAllCommands();
        Employee* getFirstAvailableEmployee();
        bool pay(float amountPaid);
        bool placeOrder(Plant* plants);

    private:
        std::vector<Employee*> allEmployees;
        std::vector<Command*> commands;
        Order* order;
};

#endif