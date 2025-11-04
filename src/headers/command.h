/**
 * @file command.h
 * @brief Declares the command hierarchy used for greenhouse task delegation.
 *
 * Covers plant care commands, maintenance actions, and front-desk customer
 * request commands executed by the employee chain of responsibility.
 */
#ifndef COMMAND_H
#define COMMAND_H
#include <string>

class GardenComponent;
class Employee;
class Plant;

/** @brief Preferred sunlight exposure for advice requests. */
enum class SunlightPreference { UNKNOWN, LOW, MEDIUM, HIGH };
/** @brief Preferred watering frequency for advice requests. */
enum class WaterPreference { UNKNOWN, LOW, MEDIUM, HIGH };

/** @brief Type of maintenance an employee must perform. */
enum class MaintenanceType {
    WATER,
    MOVE
};

/** @brief Categories of commands routed through the employee chain. */
enum CommandType {
    PLANT_COMMAND,
    MAINTENANCE_COMMAND,
    REQUEST_COMMAND
};

/**
 * @brief Criteria describing desired care characteristics for advice.
 */
struct AdviceCriteria {
    SunlightPreference sunlight = SunlightPreference::UNKNOWN;
    WaterPreference water = WaterPreference::UNKNOWN;
};

/**
 * @brief Base command interface executed by employees.
 */
class Command {
public:
    virtual ~Command() {}
    /**
     * @brief Executes the command using the supplied employee.
     * @param emp Employee responsible for the action.
     */
    virtual void execute(Employee* emp) = 0;
    /**
     * @brief Reports the command category.
     * @return Command classification.
     */
    virtual CommandType getType() const = 0;
};

//Sender -> A Plant/GardenSection, Receiver -> Caretaker
/**
 * @brief Command instructing an employee to tend to a specific plant.
 */
class PlantCommand : public Command {
private:
    Plant* plant;
public:
    /**
     * @brief Binds the command to a particular plant.
     * @param p Target plant needing care.
     */
    PlantCommand(Plant* p) : plant(p) {}
    /**
     * @brief Instructs the caretaker to service the plant.
     */
    void execute(Employee* employee) override;
    /**
     * @brief Reports the command type.
     */
    CommandType getType() const override;
};

//Sender -> Front Desk, Receiver -> Caretaker
/**
 * @brief Command describing a maintenance action for a garden component.
 */
class Maintenance : public Command {
private:
    GardenComponent* target;
    MaintenanceType type;
public:
    /**
     * @brief Constructs a maintenance command.
     * @param t Component requiring maintenance.
     * @param mt Maintenance action type.
     */
    Maintenance(GardenComponent* t, MaintenanceType mt)
        : target(t), type(mt) {}

    /**
     * @brief Dispatches the maintenance action to the provided employee.
     */
    void execute(Employee* emp) override;

    /**
     * @brief Identifies this command as maintenance.
     */
    CommandType getType() const override;
    /**
     * @brief Accesses the maintenance category.
     * @return Maintenance type.
     */
    MaintenanceType getMaintenanceType() const { return type; }
};

//Sender -> FrontDesk, Receiver -> Chain of Employees
enum RequestType { COMPLAINT, ESCALATION, ADVICE };

/**
 * @brief Command containing a customer request routed through employees.
 */
class RequestCommand : public Command {
private:
    RequestType type;
    std::string message;
    AdviceCriteria advice;
public:
    /**
     * @brief Creates a generic request command.
     * @param t Request category.
     * @param msg Message associated with the request.
     */
    RequestCommand(RequestType t, const std::string& msg) : type(t), message(msg) {}
    /**
     * @brief Creates an advice request using pre-populated criteria.
     * @param a Advice characteristics.
     */
    RequestCommand(const AdviceCriteria& a): type(RequestType::ADVICE), advice(a) {}
    /**
     * @brief Executes the request by forwarding it through the chain.
     */
    void execute(Employee* emp) override;

    /**
     * @brief Reports the command type.
     */
    CommandType getType() const override;
    /**
     * @brief Returns the advice criteria for ADVICE requests.
     */
    AdviceCriteria getCriteria() const { return advice; }
    /**
     * @brief Retrieves the request category.
     */
    RequestType getRequestType() const;
    /**
     * @brief Provides the customer message associated with the request.
     */
    std::string getMessage() const;
};

#endif
