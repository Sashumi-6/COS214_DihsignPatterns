/**
 * @file command.cpp
 * @brief Implements command execution logic for greenhouse employees.
 */
#include "../headers/command.h"
#include "../headers/employee.h"

/**
 * @brief Executes maintenance actions using caretaker employees.
 */
void Maintenance::execute(Employee* emp) {
        Caretaker* c = dynamic_cast<Caretaker*>(emp);
       if(c) c->performMaintenance(target, type);  //fixed
    }

/**
 * @brief Identifies plant commands as plant-related.
 */
CommandType PlantCommand::getType() const {
        return PLANT_COMMAND;
    }

/**
 * @brief Identifies maintenance commands as maintenance-related.
 */
    CommandType Maintenance::getType() const {
        return MAINTENANCE_COMMAND;
    }
/**
 * @brief Executes plant commands by requesting caretakers to plant new flora.
 */
void PlantCommand::execute(Employee* e) {
    Caretaker* c = dynamic_cast<Caretaker*>(e);
        if(c) c->plantNewPlant(plant);
        // else ignore / error
}

/**
 * @brief Executes request commands by delegating further along the chain.
 */
void RequestCommand::execute(Employee* emp) {
        emp->handleRequest(this);
    }

/**
 * @brief Identifies request commands as such.
 */
    CommandType RequestCommand::getType() const { return REQUEST_COMMAND; }

/**
 * @brief Retrieves the stored request type.
 */
    RequestType RequestCommand::getRequestType() const { return type; }
/**
 * @brief Returns the stored request message.
 */
    std::string RequestCommand::getMessage() const { return message; }
