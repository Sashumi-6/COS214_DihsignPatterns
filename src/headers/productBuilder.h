#ifndef PRODUCTBUILDER_H
#define PRODUCTBUILDER_H

#include "inventory.h"
class Plant;
class Product;

class Bob {
    public:
        Bob(Plant* plant);
        virtual void addPlant() = 0;
        virtual void addSoil() = 0;
        virtual void setContainer() = 0;

    protected:
        Inventory Inventory;
};

class BouquetBuilder : public Bob {
    public:
        BouquetBuilder(Plant* plant);
        void addPlant();
        void addSoil(); // stubbed
        void setContainer();
        Product* getProduct();

    protected:
        int numberOfPlants;
};

class BasicBuilder : public Bob {
    public:
        BasicBuilder(Plant* plant);
        void addPlant();
        void addSoil();
        void setContainer();
        Product* getProduct();
};

#endif