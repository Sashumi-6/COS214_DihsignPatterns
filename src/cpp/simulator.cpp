/**
 * @file simulator.cpp
 * @brief Implements the greenhouse business simulation workflow.
 */
#include "../headers/simulator.h"

#include "../headers/command.h"
#include "../headers/garden.h"
#include "../headers/iterator.h"
#include "../headers/plant.h"
#include <sstream>
#include <stdexcept>

namespace {

constexpr int kMaxSimulationDays = 30;
constexpr double kDefaultPlantPrice = 15.0;

/**
 * @brief Converts a business level into a lowercase string.
 * @param level Business volume enumeration.
 * @return String representation of the level.
 */
std::string toString(BusinessLevel level) {
    switch (level) {
        case BusinessLevel::LOW:
            return "low";
        case BusinessLevel::MEDIUM:
            return "medium";
        case BusinessLevel::HIGH:
            return "high";
    }
    return "unknown";
}

} // namespace

Simulation::Simulation(int days)
    : frontDesk(nullptr),
      greenhouseRoot(nullptr),
      greenhouseManager(nullptr),
      numDays(1),
      manualCustomerIndex(0),
      generatedCustomerCount(0) {
    customerNamePool = {"Alex", "Morgan", "Riley", "Taylor", "Jordan", "Casey",
                        "Jamie", "Dakota", "Harper", "Rowan", "Charlie", "Avery"};
    std::random_device rd;
    rng.seed(rd());
    setNumDays(days);
}

Simulation::~Simulation() {
    cleanup();
}

void Simulation::setNumDays(int days) {
    if (days < 1) {
        days = 1;
    }
    if (days > kMaxSimulationDays) {
        days = kMaxSimulationDays;
    }
    numDays = days;
    if (static_cast<int>(businessSchedule.size()) > numDays) {
        businessSchedule.resize(numDays);
    }
}

void Simulation::configureBusinessLevels(const std::vector<BusinessLevel>& levels) {
    businessSchedule = levels;
    if (static_cast<int>(businessSchedule.size()) > numDays) {
        businessSchedule.resize(numDays);
    }
    generateBusinessLevelsAutomatically = false;
}

void Simulation::autoGenerateBusinessLevels(bool enable) {
    generateBusinessLevelsAutomatically = enable;
}

void Simulation::configureEmployees(int totalEmployees) {
    if (totalEmployees < 3) {
        throw std::invalid_argument("Simulation requires at least 3 employees.");
    }
    configuredEmployeeCount = totalEmployees;
}

void Simulation::configurePlantSelection(const std::map<std::string, int>& selection) {
    const auto& database = PlantDatabase::getAllPlants();
    for (const auto& entry : selection) {
        if (entry.second < 0) {
            throw std::invalid_argument("Plant quantities cannot be negative.");
        }
        if (database.find(entry.first) == database.end()) {
            throw std::invalid_argument("Unknown plant type selected: " + entry.first);
        }
    }
    plantSelection = selection;
}

void Simulation::setRandomSeed(unsigned int seed) {
    configuredSeed = seed;
    seedConfigured = true;
    rng.seed(seed);
}

const std::vector<DaySummary>& Simulation::getDailySummaries() const {
    return dailySummaries;
}

const std::vector<std::string>& Simulation::getEventLog() const {
    return eventLog;
}

GreenHouseManager* Simulation::getGreenHouseManager() {
    return greenhouseManager;
}

void Simulation::startSimulation() {
    ensurePrepared();
    dailySummaries.clear();
    eventLog.clear();
    generatedCustomerCount = 0;
    manualCustomerIndex = 0;

    std::ostringstream oss;
    oss << "Simulation starting for " << numDays << " day(s).";
    log(oss.str());

    for (int day = 0; day < numDays; ++day) {
        DaySummary summary;
        summary.dayIndex = day + 1;
        summary.businessLevel = businessSchedule[day];
        log("Day " + std::to_string(summary.dayIndex) + " (" + toString(summary.businessLevel) + ") begins.");

        scheduleMaintenance(summary);
        frontDesk->executeAllCommands();

        runCustomersForDay(day, summary);
        frontDesk->executeAllCommands();

        if (greenhouseManager) {
            greenhouseManager->clearAllDead();
        }

        dailySummaries.push_back(summary);
        log("Day " + std::to_string(summary.dayIndex) + " completed.");
    }
}

bool Simulation::addCustomer(Customer* customer) {
    if (customer == nullptr) {
        return false;
    }
    manualCustomers.push_back(customer);
    return true;
}

bool Simulation::addEmployee(std::string employeeType) {
    return !employeeType.empty();
}

void Simulation::setWeather() {}

void Simulation::addPlant(Plant* plant, GardenSection* gardenSection) {
    if (gardenSection == nullptr || plant == nullptr) {
        return;
    }
    gardenSection->add(plant);
}

void Simulation::ensurePrepared() {
    if (!seedConfigured) {
        std::random_device rd;
        rng.seed(rd());
    }

    cleanup();

    greenhouseRoot = new GardenSection();
    greenhouseManager = new GreenHouseManager(greenhouseRoot, "root");
    frontDesk = new FrontDesk();
    frontDesk->setGreenhouse(greenhouseRoot);

    employeeStorage.clear();

    populateGreenhouse();
    initialiseEmployees();
    buildBusinessSchedule();
}

void Simulation::initialiseEmployees() {
    ManagerFactory managerFactory;
    CashierFactory cashierFactory;
    CaretakerFactory caretakerFactory;

    Employee* managerBase = managerFactory.createEmployee();
    Employee* cashierBase = cashierFactory.createEmployee();
    Manager* manager = dynamic_cast<Manager*>(managerBase);
    Cashier* cashier = dynamic_cast<Cashier*>(cashierBase);

    if (manager == nullptr || cashier == nullptr) {
        delete managerBase;
        delete cashierBase;
        throw std::runtime_error("Failed to create manager or cashier.");
    }

    manager->setGreenhouse(greenhouseRoot);
    cashier->setGreenhouse(greenhouseRoot);

    cashier->setNext(manager);

    frontDesk->addEmployee(cashier);
    frontDesk->addEmployee(manager);

    employeeStorage.push_back(cashier);
    employeeStorage.push_back(manager);

    int caretakersToCreate = configuredEmployeeCount - 2;
    for (int i = 0; i < caretakersToCreate; ++i) {
        Employee* caretakerBase = caretakerFactory.createEmployee();
        if (!caretakerBase) {
            continue;
        }
        caretakerBase->setGreenhouse(greenhouseRoot);
        if (Caretaker* caretakerPtr = dynamic_cast<Caretaker*>(caretakerBase)) {
            caretakerPtr->setHomeSection(greenhouseRoot);
            frontDesk->addEmployee(caretakerPtr);
        }
        employeeStorage.push_back(caretakerBase);
    }
}

void Simulation::populateGreenhouse() {
    const auto& database = PlantDatabase::getAllPlants();

    if (plantSelection.empty()) {
        int count = 0;
        for (const auto& entry : database) {
            plantSelection[entry.first] = 2;
            if (++count >= 5) {
                break;
            }
        }
    }

    for (const auto& entry : plantSelection) {
        auto it = database.find(entry.first);
        if (it == database.end()) {
            continue;
        }
        const PlantInfo& info = it->second;
        for (int i = 0; i < entry.second; ++i) {
            Plant* plant = createPlantInstance(entry.first, info);
            greenhouseManager->addPlant(plant);
        }
    }
}

void Simulation::buildBusinessSchedule() {
    if (generateBusinessLevelsAutomatically || businessSchedule.size() != static_cast<std::size_t>(numDays)) {
        businessSchedule.assign(static_cast<std::size_t>(numDays), BusinessLevel::MEDIUM);
    }

    if (generateBusinessLevelsAutomatically) {
        std::uniform_int_distribution<int> levelDist(0, 2);
        for (int day = 0; day < numDays; ++day) {
            businessSchedule[static_cast<std::size_t>(day)] =
                static_cast<BusinessLevel>(levelDist(rng));
        }
    } else if (businessSchedule.size() < static_cast<std::size_t>(numDays)) {
        businessSchedule.resize(static_cast<std::size_t>(numDays), BusinessLevel::MEDIUM);
    }
}

void Simulation::scheduleMaintenance(DaySummary& summary) {
    if (!greenhouseRoot || !frontDesk) {
        return;
    }

    SectionOnlyIterator iterator(greenhouseRoot);
    for (GardenComponent* section = iterator.first(); section != nullptr; section = iterator.next()) {
        frontDesk->addCommand(new Maintenance(section, MaintenanceType::WATER));
        summary.maintenanceCommands++;
        frontDesk->addCommand(new Maintenance(section, MaintenanceType::MOVE));
        summary.maintenanceCommands++;
    }
}

void Simulation::runCustomersForDay(int /*dayIndex*/, DaySummary& summary) {
    const int baseCustomers = customersForLevel(summary.businessLevel);
    int manualRemaining = 0;
    if (manualCustomerIndex < manualCustomers.size()) {
        manualRemaining = static_cast<int>(manualCustomers.size() - manualCustomerIndex);
    }

    const int totalCustomers = baseCustomers + manualRemaining;
    if (totalCustomers <= 0) {
        return;
    }

    std::bernoulli_distribution orderDecision(0.6);

    for (int i = 0; i < totalCustomers; ++i) {
        Customer* customerPtr = nullptr;
        bool ownsCustomer = false;
        bool wantsOrder = false;

        if (manualCustomerIndex < manualCustomers.size()) {
            customerPtr = manualCustomers[manualCustomerIndex++];
            wantsOrder = customerPtr ? customerPtr->wantsOrder() : false;
        } else {
            wantsOrder = orderDecision(rng) && !plantSelection.empty();
            customerPtr = new Customer(generateCustomerName(), wantsOrder);
            ownsCustomer = true;
        }

        if (customerPtr == nullptr) {
            if (ownsCustomer) {
                delete customerPtr;
            }
            continue;
        }

        summary.customersServed++;

        if (wantsOrder) {
            auto requests = generateOrderRequests();
            if (!requests.empty() && frontDesk->placeOrder(requests, customerPtr)) {
                summary.ordersCompleted++;
                log("Order placed for " + customerPtr->getName());
                frontDesk->pay();
                if (ownsCustomer) {
                    delete customerPtr;
                }
                continue;
            }
            wantsOrder = false;
        }

        frontDesk->addCommand(new RequestCommand(generateRandomQuery()));
        summary.queriesAnswered++;
        log("Advice request logged for " + customerPtr->getName());

        if (ownsCustomer) {
            delete customerPtr;
        }
    }
}

std::vector<ProductRequest> Simulation::generateOrderRequests() {
    std::vector<ProductRequest> requests;
    if (plantSelection.empty()) {
        return requests;
    }

    std::vector<std::string> plantTypes;
    plantTypes.reserve(plantSelection.size());
    for (const auto& entry : plantSelection) {
        plantTypes.push_back(entry.first);
    }

    if (plantTypes.empty()) {
        return requests;
    }

    std::uniform_int_distribution<int> productCountDist(1, 2);
    std::uniform_int_distribution<int> plantIndexDist(0, static_cast<int>(plantTypes.size()) - 1);
    std::uniform_int_distribution<int> plantsPerProductDist(1, 3);
    std::bernoulli_distribution wantsCardDist(0.35);
    std::bernoulli_distribution wantsWrapDist(0.5);

    int productCount = productCountDist(rng);
    for (int i = 0; i < productCount; ++i) {
        ProductRequest request;
        int plantsNeeded = plantsPerProductDist(rng);
        for (int p = 0; p < plantsNeeded; ++p) {
            const std::string& plantName = plantTypes[plantIndexDist(rng)];
            if (!hasMaturePlantAvailable(plantName)) {
                continue;
            }
            request.plantNames.push_back(plantName);
        }
        if (request.plantNames.empty()) {
            continue;
        }
        request.wantsCard = wantsCardDist(rng);
        if (request.wantsCard) {
            request.cardMessage = "With love";
        }
        request.wantsWrapping = wantsWrapDist(rng);
        requests.push_back(request);
    }
    return requests;
}

RequestCommand Simulation::generateRandomQuery() {
    const auto& database = PlantDatabase::getAllPlants();
    if (plantSelection.empty() || database.empty()) {
        return RequestCommand(RequestType::COMPLAINT, "No plants available yet.");
    }

    std::vector<std::string> candidates;
    candidates.reserve(plantSelection.size());
    for (const auto& entry : plantSelection) {
        if (database.find(entry.first) != database.end()) {
            candidates.push_back(entry.first);
        }
    }
    if (candidates.empty()) {
        return RequestCommand(RequestType::COMPLAINT, "No valid plants configured.");
    }

    std::uniform_int_distribution<int> plantIndexDist(0, static_cast<int>(candidates.size()) - 1);
    const std::string& chosen = candidates[plantIndexDist(rng)];
    const PlantInfo& info = database.at(chosen);

    AdviceCriteria criteria;
    criteria.sunlight = info.sunlight;
    criteria.water = info.water;
    return RequestCommand(criteria);
}

std::string Simulation::generateCustomerName() {
    if (customerNamePool.empty()) {
        return "Customer_" + std::to_string(++generatedCustomerCount);
    }
    const std::string& base = customerNamePool[static_cast<std::size_t>(generatedCustomerCount % customerNamePool.size())];
    ++generatedCustomerCount;
    return base + " #" + std::to_string(generatedCustomerCount);
}

int Simulation::customersForLevel(BusinessLevel level) const {
    switch (level) {
        case BusinessLevel::LOW:
            return 2;
        case BusinessLevel::MEDIUM:
            return 5;
        case BusinessLevel::HIGH:
            return 8;
    }
    return 0;
}

Plant* Simulation::createPlantInstance(const std::string& name, const PlantInfo& info) {
    WaterLossStrategy* water = createWaterStrategy(info.water);
    SunlightStrategy* sun = createSunStrategy(info.sunlight);
    auto* state = new MatureState(nullptr);
    return new Plant(name, kDefaultPlantPrice, water, sun, state);
}

WaterLossStrategy* Simulation::createWaterStrategy(WaterPreference preference) {
    switch (preference) {
        case WaterPreference::LOW:
            return new LowWaterLoss();
        case WaterPreference::MEDIUM:
            return new MedWaterLoss();
        case WaterPreference::HIGH:
            return new HighWaterLoss();
        default:
            return new MedWaterLoss();
    }
}

SunlightStrategy* Simulation::createSunStrategy(SunlightPreference preference) {
    switch (preference) {
        case SunlightPreference::LOW:
            return new LowSunlightStrategy();
        case SunlightPreference::MEDIUM:
            return new MedSunlightStrategy();
        case SunlightPreference::HIGH:
            return new HighSunlightStrategy();
        default:
            return new MedSunlightStrategy();
    }
}

void Simulation::log(const std::string& entry) {
    eventLog.push_back(entry);
}

std::string Simulation::businessLevelToString(BusinessLevel level) const {
    return toString(level);
}

bool Simulation::hasMaturePlantAvailable(const std::string& plantName) const {
    if (!greenhouseManager) {
        return false;
    }
    return greenhouseManager->findMature(plantName) != nullptr;
}

void Simulation::cleanup() {
    if (frontDesk) {
        delete frontDesk;
        frontDesk = nullptr;
    }
    clearEmployees();
    if (greenhouseManager) {
        delete greenhouseManager;
        greenhouseManager = nullptr;
    }
    if (greenhouseRoot) {
        destroyGardenComponent(greenhouseRoot);
        greenhouseRoot = nullptr;
    }
}

void Simulation::clearEmployees() {
    for (std::size_t i = 0; i < employeeStorage.size(); ++i) {
        delete employeeStorage[i];
    }
    employeeStorage.clear();
}

void Simulation::destroyGardenComponent(GardenComponent* component) {
    if (!component) {
        return;
    }

    if (!component->isLeaf()) {
        std::vector<GardenComponent*> children = component->getChildren();
        for (std::size_t i = 0; i < children.size(); ++i) {
            destroyGardenComponent(children[i]);
        }
    }
    delete component;
}
