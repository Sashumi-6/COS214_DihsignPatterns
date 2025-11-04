#ifndef ITERATOR_H
#define ITERATOR_H

#include <queue>
#include <stack>

#include "../headers/garden.h"

template <typename T> class Iterator {
  public:
    virtual T* first() = 0;
    virtual T* next() = 0;
    virtual bool isDone() const = 0;
    // virtual T* currentItem() = 0;
};

class PlantOnlyIterator : public Iterator<GardenComponent> {
  public:
    explicit PlantOnlyIterator(GardenComponent* root);
    GardenComponent* first() override;
    GardenComponent* next() override;
    bool isDone() const override;

  private:
    std::stack<GardenComponent*> stack;
    GardenComponent* root;
};

class SectionOnlyIterator : public Iterator<GardenComponent> {
  public:
    explicit SectionOnlyIterator(GardenComponent* root);
    GardenComponent* first() override;
    GardenComponent* next() override;
    bool isDone() const override;

  private:
    std::stack<GardenComponent*> stack;
    GardenComponent* root;
};

class FullIterator : public Iterator<GardenComponent> {
  public:
    explicit FullIterator(GardenComponent* root);
    GardenComponent* first() override;
    GardenComponent* next() override;
    bool isDone() const override;

  private:
    std::queue<GardenComponent*> queue;
    GardenComponent* root;
};

#endif
