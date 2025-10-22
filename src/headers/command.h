#ifndef COMMAND_H
#define COMMAND_H

class GardenComponent;
class Employee;
class Plant;

class Command {
    public:
        virtual void execute() = 0;

    protected:
        GardenComponent* GreenHouse;
};

class PlantCommand : public Command {
    public:
        PlantCommand(Plant* plant);
        void execute();
};

class Maintenance : public Command {
    public:
        void execute();
};

class ArrangeCommand : public Command {
    public:
        ArrangeCommand(Plant* plant);
        void execute();
        void execute(Employee* worker);
};

#endif