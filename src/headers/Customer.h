#ifndef CUSTOMER_H
#define CUSTOMER_H
//we call a customer constructor in simulation, we destroy customer at end too

#include <string>
#include <vector>
#include "../headers/command.h"


class Customer{

    private:
    bool order; // if true then customer wants order, if false, they want to ask a question
    std::string name;

    public:
    Customer();
    Customer(const std::string& name, bool wantsOrder = true);
    Customer* createCustomerOrder();
    RequestCommand createCustomerQuery();
    std::string getName();
    bool wantsOrder() const;

    
};

#endif
