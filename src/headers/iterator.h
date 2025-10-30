#ifndef ITERATOR_H
#define ITERATOR_H

#include "garden.h"

template <typename T>
class Iterator {
    public:
        virtual T* first() = 0;
        virtual T* next() = 0;
        virtual bool isDone() = 0;
        virtual T* currentItem() = 0;
};

class GardenIterator : public Iterator<GardenComponent> {
    public:
        GardenComponent* first();
        GardenComponent* next();
        bool isDone();
        GardenComponent* currentItem();
};

#endif