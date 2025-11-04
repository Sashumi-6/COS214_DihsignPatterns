#ifndef PRODUCTBUILDER_H
#define PRODUCTBUILDER_H

#include <vector>
#include <string>
#include "plant.h"

#include "inventory.h"
#include "garden.h"
class GardenComponent; // forward declaration for pointer usage in Product
class Product;  // forward declaration for pointer usage in Bob


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
        std::string getName() const { 
        return plant ? plant->getName() : "Unknown Product"; 
   
}
        virtual ~Product(){
            if (plant) {
                delete plant;
                plant = nullptr;
            }
        }
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

        std::string getSoil() const {
            return soil;
        }

        std::string getContainer() const {
            return container;
        }

        std::string getCard() const {
            return card;
        }

        std::string getWrapping() const {
            return wrapping;
        }



        float getPrice() const {
            return price;
        }

        void  incPrice(float amount){
            price += amount;
        }

        void setWrapping(const std::string& w);

};
class Bob {
    public:
        Bob(std::vector<Plant*> plant, GardenComponent* greenhouse) : plants(plant), greenhouse(greenhouse) {};
        virtual Product* addPlant() = 0;
         Product* addSoil(Product* product);
        virtual Product* setContainer(Product* product) = 0;
        virtual Product* getProduct() = 0;
        virtual ~Bob();
    protected:
        //TODO Moved to product
        std::vector<Plant*> plants; //TODO add to UML
        GardenComponent* greenhouse;

};

class BouquetBuilder : public Bob {
    public:
        BouquetBuilder(std::vector<Plant*> plant, GardenComponent* greenhouse); // TODO change in UML
        Product* addPlant() override;
        Product* setContainer(Product* product) override;
        Product* getProduct();
};

class BasicBuilder : public Bob {
    public:
        BasicBuilder(std::vector<Plant*> plants, GardenComponent* greenhouse) ; // TODO change in UML
        Product* addPlant();
    
        Product* setContainer(Product* product) override;
        Product* getProduct();
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
