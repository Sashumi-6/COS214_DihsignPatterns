#ifndef GARDEN_H
#define GARDEN_H

#include <vector>

template <typename T> class Iterator;
class GardenIterator;

class GardenComponent {
  public:
    virtual void waterPlant() = 0;
    virtual void exposeToSunlight() = 0;
    virtual void loseWater() = 0;
    GardenComponent() = default;
    GardenComponent(const GardenComponent&) = default;
    GardenComponent& operator=(const GardenComponent&) = default;
    GardenComponent(GardenComponent&&) noexcept = default;
    GardenComponent& operator=(GardenComponent&&) noexcept = default;
    virtual ~GardenComponent() = default;
    virtual bool canSell() = 0;
    virtual void grow() = 0;
    virtual void add(GardenComponent* param) = 0;
    virtual GardenComponent* getChild(int param) = 0;
    virtual void remove(GardenComponent* param) = 0;
    virtual Iterator<GardenComponent>* createIterator() = 0;
};

class GardenSection : public GardenComponent { ///TODO THIS IS JUST HERE FOR TESTING PLEASE CHANGE!!!!!!!!!!! 
  public:
    void waterPlant() override;
    void exposeToSunlight() override;
    void loseWater() override;
    bool canSell() override;
    void grow();
    void add(GardenComponent* param);
    GardenComponent* getChild(int param) override;
    void remove(GardenComponent* param) override;
    Iterator<GardenComponent>* createIterator() override;
  private:
    std::vector<GardenComponent*> children;
};

#endif
