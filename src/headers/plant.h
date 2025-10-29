#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "garden.h"

enum class PlantLocation {
    OUTSIDE,
    GREENHOUSE,
    INSIDE
};

class Plant : public GardenComponent {
    public:
        void waterPlant();
        void exposeToSunlight();
        void loseWater();
        bool canSell();
        void grow();
        void setState(PlantState* state);

    private:
        double price;
        std::string name;
};

class PlantState {
    public:
        virtual void handleWaterPlant() = 0;
        virtual void handleExposeToSunlight() = 0;
        virtual bool canSell() = 0;
        virtual void handleGrow() = 0;

    protected:
        GardenComponent* plant;
};

class SeedlingState : public PlantState {
    public:
        void handleWaterPlant();
        void handleExposeToSunlight();
        bool canSell();
        void handleGrow();
};

class MatureState : public PlantState {
    public:
        void handleWaterPlant();
        void handleExposeToSunlight();
        bool canSell();
        void handleGrow();
};

class DeadState : PlantState {
    public:
        void handleWaterPlant();
        void handleExposeToSunlight();
        bool canSell();
        void handleGrow();
};

#endif