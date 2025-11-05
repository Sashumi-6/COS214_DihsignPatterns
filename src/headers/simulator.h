/**
 * @file simulator.h
 * @brief Declares the greenhouse simulation orchestrating daily operations.
 *
 * Defines business level scheduling, daily summaries, and helper utilities
 * used to simulate customer interactions over multiple days.
 */
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

/** @brief Represents expected business volume for a simulation day. */
enum class BusinessLevel { LOW = 0, MEDIUM = 1, HIGH = 2 };

/**
 * @brief Captures a summary of outcomes for a single simulation day.
 */
struct DaySummary {
    int dayIndex = 0;
    BusinessLevel businessLevel = BusinessLevel::LOW;
    int customersServed = 0;
    int ordersCompleted = 0;
    int queriesAnswered = 0;
    int maintenanceCommands = 0;
};

/**
 * @brief High-level controller running the greenhouse business simulation.
 */
class Simulation {
public:
    /**
     * @brief Constructs a simulation for the specified number of days.
     * @param numDays Number of days to simulate.
     */
    Simulation(int numDays = 1);
    /**
     * @brief Releases resources owned by the simulation instance.
     */
    ~Simulation();
    /**
     * @brief Starts the simulation, iterating over scheduled days.
     */
    void startSimulation();
    /**
     * @brief Adjusts the number of days in the simulation run.
     */
    void setNumDays(int days);
    /**
     * @brief Supplies a pre-defined business level sequence.
     */
    void configureBusinessLevels(const std::vector<BusinessLevel>& levels);
    /**
     * @brief Enables or disables auto-generation of business levels.
     */
    void autoGenerateBusinessLevels(bool enable);
    /**
     * @brief Configures the total number of employees to schedule.
     */
    void configureEmployees(int totalEmployees);
    /**
     * @brief Configures plants to stock for the simulation.
     */
    void configurePlantSelection(const std::map<std::string, int>& selection);
    /**
     * @brief Seeds the random number generator.
     */
    void setRandomSeed(unsigned int seed);
    /**
     * @brief Retrieves daily summary results after running the simulation.
     */
    const std::vector<DaySummary>& getDailySummaries() const;
    /**
     * @brief Returns chronological event log entries.
     */
    const std::vector<std::string>& getEventLog() const;
    /**
     * @brief Provides access to the greenhouse manager.
     */
    GreenHouseManager* getGreenHouseManager();
    /**
     * @brief Adds a customer to the manual processing queue.
     */
    bool addCustomer(Customer* customer);
    /**
     * @brief Adds an employee of a given type to the simulation.
     * @param employeeType Name identifying the employee role.
     */
    bool addEmployee(std::string employeeType);
    /**
     * @brief Randomly sets weather conditions influencing plant care.
     */
    void setWeather();
    /**
     * @brief Adds a plant to a specified garden section.
     */
    void addPlant(Plant* plant, GardenSection* gardenSection);

private:
    /** Ensures resources are initialized before running. */
    void ensurePrepared();
    /** Creates employee instances according to configuration. */
    void initialiseEmployees();
    /** Populates the greenhouse with initial plants. */
    void populateGreenhouse();
    /** Builds the schedule of business levels per day. */
    void buildBusinessSchedule();
    /** Schedules recurring maintenance tasks. */
    void scheduleMaintenance(DaySummary& summary);
    /** Runs all customers scheduled for a particular day. */
    void runCustomersForDay(int dayIndex, DaySummary& summary);
    /** Generates product requests for an order. */
    std::vector<ProductRequest> generateOrderRequests();
    /** Produces a random customer query command. */
    RequestCommand generateRandomQuery();
    /** Generates a random customer name. */
    std::string generateCustomerName();
    /** Resolves number of customers for a business level. */
    int customersForLevel(BusinessLevel level) const;
    /** Creates a specific plant instance using database metadata. */
    Plant* createPlantInstance(const std::string& name, const PlantInfo& info);
    /** Instantiates water-loss strategy based on preference. */
    WaterLossStrategy* createWaterStrategy(WaterPreference preference);
    /** Instantiates sunlight strategy based on preference. */
    SunlightStrategy* createSunStrategy(SunlightPreference preference);
    /** Records an event to the log. */
    void log(const std::string& entry);
    /** Converts business level to string. */
    std::string businessLevelToString(BusinessLevel level) const;
    /** Returns true when a mature plant of the given name exists. */
    bool hasMaturePlantAvailable(const std::string& plantName) const;
    /** Releases resources at the end of the simulation. */
    void cleanup();
    /** Clears all employees created for the simulation. */
    void clearEmployees();
    /** Recursively destroys a garden component tree. */
    void destroyGardenComponent(GardenComponent* component);

    /** Owned employee objects. */
    std::vector<Employee*> employeeStorage;
    /** Entry-point for handling customers and commands. */
    FrontDesk* frontDesk;
    /** Root of the greenhouse composite. */
    GardenSection* greenhouseRoot;
    /** Manager handling greenhouse sections and plants. */
    GreenHouseManager* greenhouseManager;
    /** Number of days to simulate. */
    int numDays;
    /** Flag controlling automatic business schedule generation. */
    bool generateBusinessLevelsAutomatically = true;
    /** Requested employee count. */
    int configuredEmployeeCount = 3;
    /** Sequence of business levels per day. */
    std::vector<BusinessLevel> businessSchedule;
    /** Plant configuration specifying quantities per name. */
    std::map<std::string, int> plantSelection;
    /** Random number generator. */
    std::mt19937 rng;
    /** Indicates whether RNG seed was explicitly set. */
    bool seedConfigured = false;
    /** Stored RNG seed when provided. */
    unsigned int configuredSeed = 0;
    /** Accumulated summaries for each simulated day. */
    std::vector<DaySummary> dailySummaries;
    /** Log entries capturing significant events. */
    std::vector<std::string> eventLog;
    /** Available customer names for random generation. */
    std::vector<std::string> customerNamePool;
    /** Customers manually inserted into the simulation. */
    std::vector<Customer*> manualCustomers;
    /** Index tracking next manual customer to process. */
    std::size_t manualCustomerIndex = 0;
    /** Number of procedurally generated customers. */
    int generatedCustomerCount = 0;
};

#endif
