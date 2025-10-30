#ifndef GARDEN_H
#define GARDEN_H

class Iterator;

class GardenComponent {
    public:
    virtual void waterPlant() = 0;
    virtual void exposeToSunlight() = 0;
    virtual void loseWater() = 0;
    virtual ~GardenComponent() = default;
    virtual bool canSell() = 0;
    virtual void grow() = 0;
    virtual void add(GardenComponent* param) = 0;
    virtual GardenComponent* getChild(int param) = 0;
    virtual void remove(GardenComponent* param) = 0;
    virtual Iterator* createIterator() = 0;
};

class GardenSection : public GardenComponent {
    public:
        void waterPlant() override;
        void exposeToSunlight() override;
        void loseWater() override;
        bool canSell() override;
        void grow() override;
        void add(GardenComponent* param) override;
        GardenComponent* getChild(int param) override;
        void remove(GardenComponent* param) override;
        Iterator* createIterator() override;
};

#endif