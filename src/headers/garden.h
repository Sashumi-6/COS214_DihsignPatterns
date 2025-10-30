#ifndef GARDEN_H
#define GARDEN_H

class Iterator;
class PlantState;

class WaterLossStrategy {
    public:
        WaterLossStrategy(float waterLevel);
        virtual float loseWater() = 0;
};

class LowWaterLoss : public WaterLossStrategy {
    public:
        float loseWater();
};

class MedWaterLoss : public WaterLossStrategy {
    public:
        float loseWater();
};

class HighWaterLoss : public WaterLossStrategy {
    public:
        float loseWater();
};

class SunlightStategy {
    public:
        virtual void exposeToSun() = 0;
};

class LowSunlightStrategy : public SunlightStategy {
    public:
        void exposeToSun();
};

class MedSunlightStrategy : public SunlightStategy {
    public:
        void exposeToSun();
};

class HighSunlightStrategy : public SunlightStategy {
    public:
        void exposeToSun();
};

class GardenComponent {
    public:
    virtual ~GardenComponent() = default;

    virtual void waterPlant() = 0;
        virtual void exposeToSunlight() = 0;
        virtual void loseWater() = 0;
        bool canSell();
        virtual void grow() = 0;
        virtual void setState(PlantState* state) = 0;
        virtual void add(GardenComponent* param) = 0;
        virtual GardenComponent* getChild(int param) = 0;
        virtual void remove(GardenComponent* param) = 0;
        Iterator* createIterator();
};

class GardenSection : public GardenComponent {
    public:
        void waterPlant();
        void exposeToSunlight();
        void loseWater();
        bool canSell();
        virtual void grow() = 0;
        void setState(PlantState* state);
        void add(GardenComponent* param);
        GardenComponent* getChild(int param);
        void remove(GardenComponent* param);
        Iterator* createIterator();
};

#endif