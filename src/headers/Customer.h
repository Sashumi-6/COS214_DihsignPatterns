#ifndef CUSTOMER_H
#define CUSTOMER_H
//we call a customer constructor in simulation, we destroy customer at end too

#include <string>
#include "command.h"
#include "frontDesk.h"


class Customer{

    private:
    bool order; // if true then customer wants order, if false, they want to ask a question
    std::string name;
    //std::vector<ProductRequest>& requests;

    public:
    Customer();
    Customer* createCustomerOrder();
    void createCustomerQuery();
    std::string getName();

    
};

#endif