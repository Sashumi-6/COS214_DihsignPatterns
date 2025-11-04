/**
 * @file frontDesk.h
 * @brief Declares the front desk facade orchestrating customer interactions.
 *
 * The front desk manages employee dispatch, command queues, and order handling
 * as the entry point for greenhouse operations.
 */
#ifndef FRONTDESK_H
#define FRONTDESK_H

#include <string>
#include <vector>
#include "command.h"
#include "employee.h"
#include "productRequest.h"

class Plant;
class GardenSection;
class GardenComponent;
class Order;
class Customer;
class Cashier;
class Caretaker;

/**
 * @brief Facade for customer interactions, routing work to employees.
 */
class FrontDesk {
public:
    /**
     * @brief Releases owned commands and orders.
     */
    ~FrontDesk();
    /**
     * @brief Handles customer queries for product availability or advice.
     */
    void query();
    /**
     * @brief Initiates the process for customers to purchase plants.
     */
    void plant();
    /**
     * @brief Schedules maintenance for greenhouse assets.
     */
    void maintain();
    /**
     * @brief Adds a command to the execution queue.
     * @param cmd Command ownership transferred to the front desk.
     */
    void addCommand(Command* cmd);
    /**
     * @brief Registers an employee with the front desk.
     * @param emp Employee to add to the roster.
     */

    void addEmployee(Employee* emp);
    /**
     * @brief Assigns a plant to a garden section within the greenhouse.
     * @param plant Plant to insert.
     * @param section Target section node.
     */
    void addPlant(Plant* plant, GardenSection* section);
    /**
     * @brief Executes all queued commands using available employees.
     */
    void executeAllCommands();
    /**
     * @brief Sets the greenhouse root component for operations.
     * @param root Composite root node.
     */
    void setGreenhouse(GardenComponent* root);
    /**
     * @brief Provides access to the greenhouse composite.
     * @return Root greenhouse component.
     */
    GardenComponent* getGreenhouse() const;

    /**
     * @brief Finds the first available employee matching the requested role.
     * @tparam T Employee subtype required.
     * @return Pointer to available employee or nullptr when none are free.
     */
    template <typename T>
    T* getAvailableEmployee();

    /**
     * @brief Processes payment for the active order.
     */
    void pay();
    /**
     * @brief Places an order based on customer product requests.
     * @param reqs Collection of requested products.
     * @param c Customer initiating the order.
     * @return True if order creation succeeds.
     */
    bool placeOrder(std::vector<ProductRequest>& reqs, Customer* c);

private:
    /** All registered employees. */
    std::vector<Employee*> employees;
    /** Currently active employee handling the operation. */
    Employee* activeEmployee = nullptr;
    /** Pending commands awaiting execution. */
    std::vector<Command*> commands;
    /** Order currently in progress. */
    Order* currentOrder = nullptr;
    /** Greenhouse composite root node. */
    GardenComponent* greenhouse = nullptr;
};

template <typename T>
T* FrontDesk::getAvailableEmployee() {
    for (Employee* e : employees) {
        if (e && e->isAvailable()) {
            if (T* casted = dynamic_cast<T*>(e)) {
                return casted;
            }
        }
    }
    return nullptr;
}

#endif
