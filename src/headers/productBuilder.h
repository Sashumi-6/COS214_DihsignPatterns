#ifndef PRODUCTBUILDER_H
#define PRODUCTBUILDER_H
#include <vector>
#include "plant.h"

#include "inventory.h"



class Bob {
    public:
        Bob(std::vector<Plant*> plant, GardenComponent* greenhouse) : plants(plant), greenhouse(greenhouse) {};
        virtual Product* addPlant() = 0;
        virtual Product* addSoil(Product* product) = 0;
        virtual Product* setContainer(Product* product) = 0;

    protected:
        //TODO Moved to product
        std::vector<Plant*> plants; //TODO add to UML
        GardenComponent* greenhouse;

};

class BouquetBuilder : public Bob {
    public:
        BouquetBuilder(std::vector<Plant*> plant, GardenComponent* greenhouse); // TODO change in UML
        Product* addPlant() override;
        Product* setContainer(Product* product);
        Product* getProduct();
};

class BasicBuilder : public Bob {
    public:
        BasicBuilder(std::vector<Plant*> plants, GardenComponent* greenhouse) ; // TODO change in UML
        Product* addPlant();
        Product* addSoil(Product* product);
        Product* setContainer(Product* product);
        Product* getProduct();
};

class Product{
    protected:
        Plant* plant;
        std::string soil;
        std::string container;
        std::string card;
        std::string wrapping;
        Inventory Inventory; // TODO add to UML
        float price;
        bool isMain;

    public:
        Product(Plant* plant, GardenComponent* greenhouse, bool isMain) : plant(plant), Inventory(greenhouse), isMain(isMain) { // greenhouse
            soil = "";
            container = "";
            card = "";
            wrapping = "";
            price = 0;
        }

         bool getisMain() const { return isMain; }

        void setPlant(Plant* p);// TODO add to UML

        // accessor to allow safe access to the plant from other objects
        Plant* getPlant() const { return plant; }
        

        void setSoil(const std::string& s);
        void setContainer(const std::string& c);

        void setCard(const std::string& c);

        float getPrice() const {
            return price;
        }

        void  incPrice(float amount){
            price += amount;
        }

        void setWrapping(const std::string& w);

};



class BouquetProduct : public Product {
    public:
        BouquetProduct(Plant* plant, GardenComponent* greenhouse,bool isMain) : Product(plant, greenhouse,isMain) {}
};

class Bouquet : public BouquetProduct {
    public:
        Bouquet(Plant* plant, GardenComponent* greenhouse, bool isMain) : BouquetProduct(plant, greenhouse,isMain) {}
        Bouquet* getNext(){return bouquet;}
        void setNext(Bouquet* bouquet){this->bouquet = bouquet;}
        float getPrice();
        
    private:
        Bouquet* bouquet; // change name in UML
        
};

//I AINT USING POTTED PRODUCT< ITS GENUINELY USELESS
class Decorator : public Product{
    private:
        Product* component;
    public:
        // initialize base Product using the wrapped product's plant (if available)
        Decorator(Product* component);
        

};

class CardDecorator : public Decorator{
    public:
        CardDecorator(Product* component, std::string cardString): Decorator(component){
            setCard(cardString);
        }
};

class WrappingPaperDecorator : public Decorator{
    public:
        WrappingPaperDecorator(Product* component, std::string wrappingString): Decorator(component){
            setWrapping(wrappingString);
        }
};

#endif