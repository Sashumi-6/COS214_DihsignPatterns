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
        void exposeToSunlight();
        void grow();
        void loseWater();
        void setState(PlantState* state);
        void waterPlant();

    private:
        WaterLossStrategy* waterLossStrategy;
        SunlightStategy* sunlightStategy;
        PlantLocation location;
        std::string name;
        PlantState* state;
        double price;
        float waterLevel;



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