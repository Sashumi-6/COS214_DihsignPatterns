#ifndef FRONTDESK_H
#define FRONTDESK_H

#include <vector>

#include "employee.h"
#include "command.h"
#include "order.h"

//This defines what exactly the customer wants in their specific product within an order
struct ProductRequest{
    std::vector<Plant*> plants;
    bool wantsWrapping = false;
    bool wantsCard = false;
    std::string cardMessage = "";
};

class FrontDesk {
    public:
        void query();
        void plant();
        void maintain();    // bool or void?
        bool addCommand(Command* cmd);
        void addEmployee();
        bool addPlant(Plant* plant, std::string section);
        void checkSpecials(Customer* customer);
        bool executeAllCommands();
        template <typename T>
        T* getAvailableEmployee();
        bool pay(float amountPaid);
        //TODO return type??
        bool placeOrder(std::vector<ProductRequest>& reqs, std::string customerName);

    private:
        Employee  *allEmployees;
        Employee* activeEmployee; 
        std::vector<Command*> commands;
        Order* currentOrder;
        //pointer to Greenhouse object of the system
        GardenComponent* greenhouse;
};

#endif