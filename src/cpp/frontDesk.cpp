#include "frontDesk.h"

void FrontDesk::addCommand(Command* cmd) {
    commands.push_back(cmd);
}

void FrontDesk::addEmployee(Employee* emp) {
    employees.push_back(emp);
}

void FrontDesk::executeAllCommands() {
    for (Command* cmd : commands) {
        // Employee* emp = getAvailableEmployee<Employee>();
        if (cmd->getType() == MAINTENANCE_COMMAND || cmd->getType() == PLANT_COMMAND) {
            Cashier* cashier = getAvailableEmployee<Cashier>();
            if (cashier) {
                cmd->execute(cashier);
            } else {
                Caretaker* caretaker = getAvailableEmployee<Caretaker>();
                if (caretaker) {
                    cmd->execute(caretaker);
                }
            }
        } else if (cmd->getType() == REQUEST_COMMAND) {
            Employee* emp = getAvailableEmployee<Employee>();
            if (emp) {
                cmd->execute(emp);
            }
        }
    }
    commands.clear();
}

void FrontDesk::addCommand(Command* cmd) {
    commands.push_back(cmd);
}

void FrontDesk::addEmployee(Employee* emp) {
    employees.push_back(emp);
}

void FrontDesk::executeAllCommands() {
    for (Command* cmd : commands) {
        // Employee* emp = getAvailableEmployee<Employee>();
        if (cmd->getType() == MAINTENANCE_COMMAND || cmd->getType() == PLANT_COMMAND) {
            Cashier* cashier = getAvailableEmployee<Cashier>();
            if (cashier) {
                cmd->execute(cashier);
            } else {
                Caretaker* caretaker = getAvailableEmployee<Caretaker>();
                if (caretaker) {
                    cmd->execute(caretaker);
                }
            }
        } else if (cmd->getType() == REQUEST_COMMAND) {
            Employee* emp = getAvailableEmployee<Employee>();
            if (emp) {
                cmd->execute(emp);
            }
        }
    }
    commands.clear();
}

bool FrontDesk::placeOrder(std::vector<ProductRequest>& requests, Customer* c){
    if(requests.empty()) return false;

    Cashier* cashier = getAvailableEmployee<Cashier>();
    currentOrder = new Order(cashier, c->getName());
    for(const auto& reqs: requests){
        currentOrder->addRequest(reqs);
    }

    currentOrder->finaliseOrder(greenhouse); //requests get handled here
    return true;
}

template <typename T>
T* FrontDesk::getAvailableEmployee() {
    for (Employee* e : employees) {
        if (e->isAvailable()) {
            if (T* casted = dynamic_cast<T*>(e)) {
                return casted;
            }
        }
    }
    return nullptr;
}


