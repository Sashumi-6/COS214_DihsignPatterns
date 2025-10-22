#ifndef FRONTDESK_H
#define FRONTDESK_H

#include "employee.h"
#include "observer.h"
#include "command.h"
#include "order.h"

class FrontDesk {
    public:
        void placeOrder(Plant* plants);
        void query();
        void pay();
        void plant();
        void maintain();
        void checkSpecials(Customer* customer);
        Employee* checkAvailableEmployee();
        void executeAll();
        void addToQueue(Command* cmd);

    private:
        Employee* employees;
        Order* order;
        Subject* specials;
        Command* commands;
};

#endif