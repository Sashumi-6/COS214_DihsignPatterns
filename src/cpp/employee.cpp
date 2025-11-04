#include "employee.h"
#include "command.h"

// -------------------- Cashier --------------------
bool Cashier::canHandle(Command* cmd) {
    if(cmd->getType() != REQUEST_COMMAND || !isAvailable()) return false;
    RequestCommand* rCmd = dynamic_cast<RequestCommand*>(cmd);
    if(!rCmd) return false;
    return rCmd->getRequestType() == COMPLAINT || rCmd->getRequestType() == ADVICE; // extend as needed
}

void Cashier::process(Command* cmd) {
    RequestCommand* rCmd = dynamic_cast<RequestCommand*>(cmd);
    if(rCmd) {
        std::cout << "Cashier handling request: " << rCmd->getMessage() << "\n";
        if(rCmd->getRequestType() == COMPLAINT) {
            std::cout << "Cashier responds to complaint: \"We understand your concerns, but have you considered taking your head out of your ass?\"";
        }else if(rCmd->getRequestType() == ADVICE){
            AdviceCriteria crit = rCmd->getCriteria();

        std::cout << "Cashier providing plant advice:\n";

            for (const auto& plant : PlantDatabase::getAllPlants()) {
                if ((crit.sunlight == SunlightPreference::UNKNOWN || plant.sunlight == crit.sunlight) &&
                    (crit.water == WaterPreference::UNKNOWN || plant.water == crit.water)) {
                    std::cout << " - " << plant.name << "\n";
                }
            }
        }
    }
}
Product* Cashier::construct(const ProductRequest& req, GardenComponent* greenhouse) {//plants are added upon Builder construction
    Bob* builder = nullptr;
    if (req.plants.size() > 1) {
        builder = new BouquetBuilder(req.plants, greenhouse);
    } else {
        builder = new BasicBuilder(req.plants, greenhouse);
    }

    //error handling if not enough plants for bouquet
    // builder->addPlant();
    //builder->getProduct();

    Product* product = builder->getProduct();
    
    if (req.wantsCard) {
        //TODO decorator logic for adding card
    }
    
    if (req.wantsWrapping) {
        //TODO decorator logic for wrapping
    }

    delete builder;
    return product;
}

void Cashier::addItem(Product* product) { order->addProduct(product); }
void Cashier::removeItem(Product* product) { order->removeProduct(product); }

// -------------------- Caretaker --------------------
bool Caretaker::canHandle(Command* cmd) {
    //Caretaker can't really handle complaints
    CommandType t = cmd->getType();
    return isAvailable() && (t == PLANT_COMMAND || t == MAINTENANCE_COMMAND);
}

void Caretaker::process(Command* cmd) {
    if(cmd->getType() == PLANT_COMMAND) {
        PlantCommand* pCmd = dynamic_cast<PlantCommand*>(cmd);
        if(pCmd) pCmd->execute(this);
    } else if(cmd->getType() == MAINTENANCE_COMMAND) {
        Maintenance* mCmd = dynamic_cast<Maintenance*>(cmd);
        if(mCmd) mCmd->execute(this);
    }
}

void Caretaker::waterPlants() { 
    if(assignedSection)assignedSection->waterPlant();
}
void Caretaker::movePlants() { 
    
    if(assignedSection)assignedSection->exposeToSunlight();
}
void Caretaker::performMaintenance(GardenComponent* target, MaintenanceType type) {
    // Assign the target section temporarily
    assignedSection = dynamic_cast<GardenSection*>(target);

    if(!assignedSection) return; // safety check

    switch(type) {
        case MaintenanceType::WATER:
            waterPlants();
            break;
        case MaintenanceType::MOVE:
            movePlants();
            break;
    }
}

void Caretaker::plantNewPlant(Plant* plant) { 
    assignedSection->add(plant);
}

// -------------------- Manager --------------------
bool Manager::canHandle(Command* cmd) {
    if(cmd->getType() != REQUEST_COMMAND) return false;
    RequestCommand* rCmd = dynamic_cast<RequestCommand*>(cmd);
    return isAvailable() && (rCmd->getRequestType() == ESCALATION || rCmd->getRequestType() == COMPLAINT);
}

void Manager::process(Command* cmd) {
    RequestCommand* rCmd = dynamic_cast<RequestCommand*>(cmd);
    if(rCmd) {
        std::cout << "Manager handling request: " << rCmd->getMessage() << "\n";
        handleEscalation();
    }
}

void Manager::handleEscalation() { numComplaints++; 
    std::cout << "Manager responds to escalation: \"We understand you're concerns, but we lowkey don't gaf :). \"";
}

// -------------------- Employee Factories --------------------
Employee* CashierFactory::createEmployee() { return new Cashier(); }
Employee* ManagerFactory::createEmployee() { return new Manager(); }
Employee* CaretakerFactory::createEmployee() { return new Caretaker(); }
