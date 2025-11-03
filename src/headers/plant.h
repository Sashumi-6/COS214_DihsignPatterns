#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "garden.h"
#include "command.h"

class PlantState;

enum class PlantLocation {
    OUTSIDE,
    GREENHOUSE,
    INSIDE
};

class WaterLossStrategy {
public:
    virtual ~WaterLossStrategy() = default;
    virtual double loseWater() = 0;
};

class LowWaterLoss : public WaterLossStrategy {
public:
    double loseWater() override;
private:
    static constexpr double kLossAmount = 0.1;
};

class MedWaterLoss : public WaterLossStrategy {
public:
    double loseWater() override;
private:
    static constexpr double kLossAmount = 0.25;
};

class HighWaterLoss : public WaterLossStrategy {
public:
    double loseWater() override;
private:
    static constexpr double kLossAmount = 0.35;
};

class SunlightStrategy {
public:
    virtual ~SunlightStrategy() = default;
    virtual PlantLocation exposeToSun() = 0;
};

class LowSunlightStrategy : public SunlightStrategy {
public:
    PlantLocation exposeToSun() override;
};

class MedSunlightStrategy : public SunlightStrategy {
public:
    PlantLocation exposeToSun() override;
};

class HighSunlightStrategy : public SunlightStrategy {
public:
    PlantLocation exposeToSun() override;
};

class Plant : public GardenComponent {
    public:
        
        static constexpr double kInitialWaterLevel = 1.0;
        static constexpr double kWaterDose = 0.35;
        Plant(std::string name , double price , WaterLossStrategy* waterLossStrategy , SunlightStrategy* sunlightStrategy , PlantState* state) ;
        Plant(const Plant& other) = default;//TODO add to UML. changeeeeeee
        
        ~Plant() override = default; // TODO change
        void waterPlant() override;
        void exposeToSunlight() override;
        void loseWater() override;
        bool canSell() override;
        void grow() override;
        void add(GardenComponent* param) override;
        GardenComponent* getChild(int param) override;
        void remove(GardenComponent* param) override;
        Iterator<GardenComponent>* createIterator() override;
        void applyWaterLoss();
        void applyExposeToSunlight();
        void setState(PlantState* newState);
        void addWater(double amount);
        
        SunlightPreference getSunlightPreference() const;
        WaterPreference getWaterPreference() const;
        std::string getName() const { return name; }
        double getPrice();

    private:
        WaterLossStrategy* waterLossStrategy;
        SunlightStrategy* sunlightStrategy;
        PlantLocation location;
        std::string name;
        PlantState* state;
        double price;
        double waterLevel;
};

class PlantState {
    public:
    virtual ~PlantState() = default;
    PlantState() ;
    PlantState* operator=(const PlantState& other);//TODO add to UML
    explicit PlantState(Plant* plant) ;
    void setPlant(Plant* newPlant) ; 
    virtual void handleWaterPlant() = 0;
    virtual void handleExposeToSunlight() = 0;
    virtual bool canSell() = 0;
    virtual void handleGrow() = 0;
    virtual void handleLoseWater() = 0;

    protected:
        Plant* plant;
};

class SeedlingState : public PlantState {
    public:
        explicit SeedlingState(Plant* plant) ;
        void handleWaterPlant() override ;
        void handleExposeToSunlight()override;
        bool canSell()override;
        void handleGrow()override;
        void handleLoseWater()override;
};

class MatureState : public PlantState {
    public:
        explicit MatureState(Plant* plant) ;
        void handleWaterPlant() override;
        void handleExposeToSunlight()override;
        bool canSell()override;
        void handleGrow()override;
        void handleLoseWater()override;
};

class DeadState : PlantState {
    public:
        explicit DeadState(Plant* plant) ;
        void handleWaterPlant() override;
        void handleExposeToSunlight()override;
        bool canSell() override;
        void handleGrow() override ;
        void handleLoseWater() override ;
};

#endif
