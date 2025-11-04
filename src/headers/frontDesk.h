#ifndef FRONTDESK_H
#define FRONTDESK_H

#include <vector>
#include "Customer.h"
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


class Customer;
class Order;
class FrontDesk {
    public:
        void query();
        void plant();
        void maintain(); 
        void addCommand(Command* cmd);
        void addEmployee(Employee* emp);
        void addPlant(Plant* plant, GardenSection* section);
        void  executeAllCommands();
        template <typename T>
        T* getAvailableEmployee();
        void pay();
        //TODO return type??
        bool placeOrder(std::vector<ProductRequest>& reqs, Customer* c);

    private:
        std::vector<Employee*> employees;
        std::vector<Command*> commands;
        Order* currentOrder;
        //pointer to Greenhouse object of the system
        GardenComponent* greenhouse;
};

#endif