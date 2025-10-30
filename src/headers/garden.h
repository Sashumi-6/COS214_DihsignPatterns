#ifndef GARDEN_H
#define GARDEN_H

class Iterator;
class PlantState;



class GardenComponent {
    public:
    virtual void waterPlant() = 0;
    virtual void exposeToSunlight() = 0;
    virtual void loseWater() = 0;
    virtual ~GardenComponent() = default;
    virtual bool canSell() = 0;
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