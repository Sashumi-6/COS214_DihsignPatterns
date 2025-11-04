#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <cstddef>
#include <map>
#include <random>
#include <string>
#include <vector>
#include "Customer.h"
#include "command.h"
#include "employee.h"
#include "frontDesk.h"
#include "greenhouseManager.h"
#include "plantDatabase.h"
#include "productRequest.h"

class GardenSection;
class GardenComponent;
class RequestCommand;

enum class BusinessLevel { LOW = 0, MEDIUM = 1, HIGH = 2 };

struct DaySummary {
    int dayIndex = 0;
    BusinessLevel businessLevel = BusinessLevel::LOW;
    int customersServed = 0;
    int ordersCompleted = 0;
    int queriesAnswered = 0;
    int maintenanceCommands = 0;
};

class Simulation {
public:
    Simulation(int numDays = 1);
    ~Simulation();
    void startSimulation();
    void setNumDays(int days);
    void configureBusinessLevels(const std::vector<BusinessLevel>& levels);
    void autoGenerateBusinessLevels(bool enable);
    void configureEmployees(int totalEmployees);
    void configurePlantSelection(const std::map<std::string, int>& selection);
    void setRandomSeed(unsigned int seed);
    const std::vector<DaySummary>& getDailySummaries() const;
    const std::vector<std::string>& getEventLog() const;
    GreenHouseManager* getGreenHouseManager();
    bool addCustomer(Customer* customer);
    bool addEmployee(std::string employeeType);
    void setWeather();
    void addPlant(Plant* plant, GardenSection* gardenSection);

private:
    void ensurePrepared();
    void initialiseEmployees();
    void populateGreenhouse();
    void buildBusinessSchedule();
    void scheduleMaintenance(DaySummary& summary);
    void runCustomersForDay(int dayIndex, DaySummary& summary);
    std::vector<ProductRequest> generateOrderRequests();
    RequestCommand generateRandomQuery();
    std::string generateCustomerName();
    int customersForLevel(BusinessLevel level) const;
    Plant* createPlantInstance(const std::string& name, const PlantInfo& info);
    WaterLossStrategy* createWaterStrategy(WaterPreference preference);
    SunlightStrategy* createSunStrategy(SunlightPreference preference);
    void log(const std::string& entry);
    std::string businessLevelToString(BusinessLevel level) const;
    bool hasMaturePlantAvailable(const std::string& plantName) const;
    void cleanup();
    void clearEmployees();
    void destroyGardenComponent(GardenComponent* component);

    std::vector<Employee*> employeeStorage;
    FrontDesk* frontDesk;
    GardenSection* greenhouseRoot;
    GreenHouseManager* greenhouseManager;
    int numDays;
    bool generateBusinessLevelsAutomatically = true;
    int configuredEmployeeCount = 3;
    std::vector<BusinessLevel> businessSchedule;
    std::map<std::string, int> plantSelection;
    std::mt19937 rng;
    bool seedConfigured = false;
    unsigned int configuredSeed = 0;
    std::vector<DaySummary> dailySummaries;
    std::vector<std::string> eventLog;
    std::vector<std::string> customerNamePool;
    std::vector<Customer*> manualCustomers;
    std::size_t manualCustomerIndex = 0;
    int generatedCustomerCount = 0;
};

#endif
