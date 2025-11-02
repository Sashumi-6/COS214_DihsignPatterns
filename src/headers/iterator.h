#ifndef ITERATOR_H
#define ITERATOR_H

#include <stack>

#include "../headers/garden.h"

template <typename T> class Iterator {
  public:
    virtual T* first() = 0;
    virtual T* next() = 0;
    virtual bool isDone() const = 0;
    // virtual T* currentItem() = 0;
};

class GardenIterator : public Iterator<GardenComponent> {
  public:
    explicit GardenIterator(GardenComponent* root);
    GardenComponent* first() override;
    GardenComponent* next() override;
    bool isDone() const override;
    // GardenComponent* currentItem() override;

  private:
    std::stack<GardenComponent*> stack;
    GardenComponent* root;
};

#endif
