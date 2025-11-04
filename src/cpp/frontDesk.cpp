#include "../headers/frontDesk.h"
#include "../headers/employee.h"
#include "../headers/Customer.h"

FrontDesk::~FrontDesk() {
    for (Command* cmd : commands) {
        delete cmd;
    }
    commands.clear();
}

void FrontDesk::maintain() {
    for (Employee* e : employees) {
        if (Caretaker* caretaker = dynamic_cast<Caretaker*>(e)) {
            if (caretaker->isAvailable()) {
                for (Command* cmd : commands) {
                    if (cmd && cmd->getType() == MAINTENANCE_COMMAND) {
                        cmd->execute(caretaker);
                    }
                }
            }
        }
    }
}

// void FrontDesk::addEmployee(Employee* emp) {
//     employees.push_back(emp);
// }

// void FrontDesk::addCommand(Command* cmd) {
//     commands.push_back(cmd);
// }

void FrontDesk::addPlant(Plant* plant, GardenSection* section) {
    section->add(plant);
}

// void FrontDesk::executeAllCommands() {
//     for (Command* cmd : commands) {
//         // Employee* emp = getAvailableEmployee<Employee>();
//         if (cmd->getType() == MAINTENANCE_COMMAND || cmd->getType() == PLANT_COMMAND) {
//             Cashier* cashier = getAvailableEmployee<Cashier>();
//             if (cashier) {
//                 cmd->execute(cashier);
//             } else {
//                 Caretaker* caretaker = getAvailableEmployee<Caretaker>();
//                 if (caretaker) {
//                     cmd->execute(caretaker);
//                 }
//             }
//         } else if (cmd->getType() == REQUEST_COMMAND) {
//             Employee* emp = getAvailableEmployee<Employee>();
//             if (emp) {
//                 cmd->execute(emp);
//             }
//         }
//     }
//     commands.clear();
// }

void FrontDesk::addCommand(Command* cmd) {
    if (cmd) {
        commands.push_back(cmd);
    }
}

void FrontDesk::addEmployee(Employee* emp) {
    employees.push_back(emp);
}

void FrontDesk::executeAllCommands() {
    for (Command* cmd : commands) {
        if (!cmd) {
            continue;
        }
        if (cmd->getType() == MAINTENANCE_COMMAND || cmd->getType() == PLANT_COMMAND) {
            Caretaker* caretaker = getAvailableEmployee<Caretaker>();
            if (caretaker) {
                cmd->execute(caretaker);
            }
        } else if (cmd->getType() == REQUEST_COMMAND) {
            Employee* emp = getAvailableEmployee<Employee>();
            if (emp) {
                cmd->execute(emp);
            }
        }
        delete cmd;
    }
    commands.clear();
}

void FrontDesk::setGreenhouse(GardenComponent* root) {
    greenhouse = root;
}

GardenComponent* FrontDesk::getGreenhouse() const {
    return greenhouse;
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

void FrontDesk::pay() {
    this->currentOrder->togglePaymentStatus();
    this->currentOrder->orderDetails();
    delete currentOrder;
    currentOrder = nullptr;
}
