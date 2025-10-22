#ifndef ITERATOR_H
#define ITERATOR_H

#include "garden.h"

class Iterator {
    public:
        virtual GardenComponent* first() = 0;
        virtual GardenComponent* next() = 0;
        virtual bool isDone() = 0;
        virtual GardenComponent* currentItem() = 0;
};

class FullCatalogueIterator : public Iterator {
    public:
        GardenComponent* first();
        GardenComponent* next();
        bool isDone();
        GardenComponent* currentItem();
};

#endif