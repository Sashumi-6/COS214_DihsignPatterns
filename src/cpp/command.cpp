#include "../headers/command.h"
#include "../headers/employee.h"


void Maintenance::execute(Employee* emp) {
        Caretaker* c = dynamic_cast<Caretaker*>(emp);
       if(c) c->performMaintenance(target, type);  //fixed
    }


CommandType PlantCommand::getType() const {
        return PLANT_COMMAND;
    }

    CommandType Maintenance::getType() const {
        return MAINTENANCE_COMMAND;
    }
void PlantCommand::execute(Employee* e) {
    Caretaker* c = dynamic_cast<Caretaker*>(e);
        if(c) c->plantNewPlant(plant);
        // else ignore / error
}

void RequestCommand::execute(Employee* emp) {
        emp->handleRequest(this);
    }

    CommandType RequestCommand::getType() const { return REQUEST_COMMAND; }

    RequestType RequestCommand::getRequestType() const { return type; }
    std::string RequestCommand::getMessage() const { return message; }
