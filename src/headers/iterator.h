#ifndef ITERATOR_H
#define ITERATOR_H

#include "../headers/garden.h"

template <typename T> class Iterator {
  public:
    virtual T* first() = 0;
    virtual T* next() = 0;
    virtual bool isDone() = 0;
    virtual T* currentItem() = 0;
};

class GardenIterator : public Iterator<GardenComponent> {
  public:
    GardenComponent* first() override;
    GardenComponent* next() override;
    bool isDone() override;
    GardenComponent* currentItem() override;
};

#endif