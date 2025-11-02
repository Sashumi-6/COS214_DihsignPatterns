#ifndef COMMAND_H
#define COMMAND_H

class GardenComponent;
class Employee;
class Plant;

// Advice request preferences
enum class SunlightPreference { UNKNOWN, LOW, MEDIUM, HIGH };
enum class WaterPreference { UNKNOWN, LOW, MEDIUM, HIGH };
enum class CareLevel { UNKNOWN, LOW, MEDIUM, HIGH };
enum CommandType {
    PLANT_COMMAND,
    MAINTENANCE_COMMAND,
    REQUEST_COMMAND
};

struct AdviceCriteria {
    SunlightPreference sunlight = SunlightPreference::UNKNOWN;
    WaterPreference water = WaterPreference::UNKNOWN;
    CareLevel care = CareLevel::UNKNOWN;
};

class Command {
public:
    virtual ~Command() {}
    virtual void execute(Employee* emp) = 0;
    virtual CommandType getType() const = 0;
};


//Sender -> A Plant/GardenSection, Receiver -> Caretaker
class PlantCommand : public Command {
    private:
        Plant* plant;
    public:
        PlantCommand(Plant* p) : plant(p) {}
        void execute(Employee* employee);
        CommandType getType() const override;
};

//Sender -> Front Desk, Receiver -> Caretaker
class Maintenance : public Command {
    private:
    GardenComponent* target;
    MaintenanceType type;
public:
     Maintenance(GardenComponent* t, MaintenanceType mt)
        : target(t), type(mt) {}

    void execute(Employee* emp) override;

    CommandType getType() const override { return MAINTENANCE_COMMAND; }
    MaintenanceType getMaintenanceType() const { return type; }
};
enum class MaintenanceType {
    WATER,
    MOVE
};

//Sender -> FrontDesk, Receiver -> Chain of Employees
enum RequestType { COMPLAINT, ESCALATION, ADVICE };

class RequestCommand : public Command {
private:
    std::string message;
    RequestType type;
public:
    RequestCommand(RequestType t, const std::string& msg) : type(t), message(msg) {}

    void execute(Employee* emp) override;

    CommandType getType() const override;

    RequestType getRequestType() const;
    std::string getMessage() const;
};

#endif