/**
 * @file Customer.h
 * @brief Declares the Customer entity used for greenhouse interactions.
 *
 * Customers can place orders or request information which is subsequently
 * routed through the front desk command system.
 */
#ifndef CUSTOMER_H
#define CUSTOMER_H
//we call a customer constructor in simulation, we destroy customer at end too

#include <string>
#include <vector>
#include "../headers/command.h"


/**
 * @brief Represents a greenhouse customer issuing orders or queries.
 */
class Customer{

    private:
    /** Indicates whether the customer intends to place an order. */
    bool order; // if true then customer wants order, if false, they want to ask a question
    /** Customer display name. */
    std::string name;

    public:
    /**
     * @brief Constructs a customer with no name and default order intent.
     */
    Customer();
    /**
     * @brief Constructs a named customer with optional order intent.
     * @param name Customer name.
     * @param wantsOrder True when the customer wants to place an order.
     */
    Customer(const std::string& name, bool wantsOrder = true);
    /**
     * @brief Prepares the customer for order placement.
     * @return Pointer to the customer for fluent chaining.
     */
    Customer* createCustomerOrder();
    /**
     * @brief Generates a query command reflecting customer questions.
     * @return Request command representing the query.
     */
    RequestCommand createCustomerQuery();
    /**
     * @brief Returns the customer's name.
     */
    std::string getName();
    /**
     * @brief Indicates whether the customer wants to place an order.
     * @return True if the customer is placing an order.
     */
    bool wantsOrder() const;


};

#endif
