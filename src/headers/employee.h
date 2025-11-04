/**
 * @file employee.h
 * @brief Declares the employee hierarchy and chain-of-responsibility behavior.
 *
 * Includes base employee functionality, specialized roles, and factories used
 * to construct staff members for the greenhouse simulation.
 */
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "command.h"
#include "productBuilder.h"
#include "order.h"

struct ProductRequest;
class GardenComponent;
class GardenSection;

class Order;
/** @brief Operational availability state for employees. */
enum EmployeeState { AVAILABLE, BUSY, ON_BREAK };

/**
 * @brief Abstract employee participating in the command handling chain.
 */
class Employee {
public:
    /**
     * @brief Virtual destructor to allow safe polymorphic cleanup.
     */
    virtual ~Employee() {}

    // Unified handler for all commands
    /**
     * @brief Handles a command or forwards it to the next employee.
     * @param cmd Command to evaluate.
     */
    void handleRequest(Command* cmd) {
        if (canHandle(cmd)) {
            process(cmd);
        } else if (nextHandler) {
            nextHandler->handleRequest(cmd);
        } else {
            std::cout << "No employee could handle this command.\n";
            //error handling
        }
    }

    /**
     * @brief Determines if the employee can process the supplied command.
     */
    virtual bool canHandle(Command* cmd) = 0;
    /**
     * @brief Performs the command-specific work.
     */
    virtual void process(Command* cmd) = 0;

    /**
     * @brief Wires the next handler in the chain of responsibility.
     * @param next Next employee to receive unhandled commands.
     */
    void setNext(Employee* next) { nextHandler = next; }
    /**
     * @brief Provides access to the next handler.
     * @return Pointer to next employee, or nullptr.
     */
    Employee* getNextHandler() const { return nextHandler; }
    /**
     * @brief Indicates whether the employee can take new assignments.
     */
    bool isAvailable() const { return state == AVAILABLE; }
    /**
     * @brief Sets the greenhouse context used for operations.
     */
    void setGreenhouse(GardenComponent* greenhousePtr);
    /**
     * @brief Retrieves the greenhouse reference.
     */
    GardenComponent* getGreenhouse() const { return greenhouse; }

protected:
    /** Descriptive role label (e.g., cashier, manager). */
    std::string role;
    /** Availability status. */
    EmployeeState state = AVAILABLE;
    /** Greenhouse composite used for operations. */
    GardenComponent* greenhouse;

private:
    /** Next link in the chain of responsibility. */
    Employee* nextHandler = nullptr;
    
};

// ================== Derived Employees ==================

/**
 * @brief Employee responsible for order processing and product assembly.
 */
class Cashier : public Employee {
public:
    /**
     * @brief Determines if the cashier can handle the given request command.
     */
    bool canHandle(Command* cmd) override;
    /**
     * @brief Processes customer-facing request commands.
     */
    void process(Command* cmd) override;

    /**
     * @brief Builds a product from a request using the builder.
     * @param req Product specification.
     * @param greenhouse Greenhouse composite for plant lookup.
     */
    Product* construct(const ProductRequest& req, GardenComponent* greenhouse);//called from Order
    /**
     * @brief Adds a product to the current order.
     */
    void addItem(Product* product);
    /**
     * @brief Removes a product from the current order.
     */
    void removeItem(Product* product);


private:
    /** Concrete builder used for assembling products. */
    Bob* builder;
    /** Order currently being fulfilled. */
    Order* order;
    /**
     * @brief Helper that maps plant names to actual plant pointers.
     */
    std::vector<Plant*> buildPlantVector(const std::vector<std::string>& names);
};

/**
 * @brief Employee responsible for plant maintenance and care.
 */
class Caretaker : public Employee {
public:
    /**
     * @brief Validates whether the caretaker should handle the command.
     */
    bool canHandle(Command* cmd) override;
    /**
     * @brief Executes caretaking operations for plants and sections.
     */
    void process(Command* cmd) override;

    /**
     * @brief Waters plants as part of maintenance routine.
     */
    void waterPlants();
    /**
     * @brief Moves plants according to maintenance requests.
     */
    void movePlants();
    /**
     * @brief Executes the specified maintenance on a target component.
     */
    void performMaintenance(GardenComponent* target, MaintenanceType type);
    /**
     * @brief Plants a new plant into the greenhouse.
     */
    void plantNewPlant(Plant* plant);
    /**
     * @brief Assigns the caretaker's home section.
     */
    void setHomeSection(GardenSection* section);
    /**
     * @brief Retrieves the caretaker's assigned section.
     */
    GardenSection* getHomeSection() const { return assignedSection; }

private:
    /** Section assigned to the caretaker. */
    GardenSection* assignedSection;
};

/**
 * @brief Employee handling escalations and managerial actions.
 */
class Manager : public Employee {
public:
    /**
     * @brief Checks if the manager should address the command.
     */
    bool canHandle(Command* cmd) override;
    /**
     * @brief Handles escalated customer situations.
     */
    void process(Command* cmd) override;

    /**
     * @brief Deals with escalated customer requests.
     */
    void handleEscalation();

private:
    /** Number of complaints processed. */
    int numComplaints = 0;
};

// ================== Employee Factories ==================

/**
 * @brief Abstract factory interface for creating employees.
 */
class EmployeeFactory {
public:
    virtual Employee* createEmployee() = 0;
};

/**
 * @brief Factory creating cashier employees.
 */
class CashierFactory : public EmployeeFactory {
public:
    Employee* createEmployee() override;
};

/**
 * @brief Factory creating manager employees.
 */
class ManagerFactory : public EmployeeFactory {
public:
    Employee* createEmployee() override;
};

/**
 * @brief Factory creating caretaker employees.
 */
class CaretakerFactory : public EmployeeFactory {
public:
    Employee* createEmployee() override;
};
