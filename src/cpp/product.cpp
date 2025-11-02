#include "../headers/productBuilder.h"

/// ////////////BouquetBuilder
BouquetBuilder::BouquetBuilder(std::vector<Plant*> plants,GardenComponent* greenhouse) : Bob(plants, greenhouse) {
    for(int i = 0; i < plants.size(); i++) {
        delete this->plants[i];
        this->plants[i] = nullptr;
    }
    plants.clear();

    for(int j = 0; j < plants.size(); j++) {
        this->plants.push_back(plants[j]);
    }

}

Product* BouquetBuilder::addPlant(){
    Bouquet* bouquet = new Bouquet(plants[0], greenhouse,true);
    bouquet->incPrice(plants[0]->getPrice());
    
    greenhouse->remove(plants[0]);
    Bouquet* node = bouquet;
    int i = 1;
    while(node != nullptr){
        if(node->getNext() == nullptr && i < plants.size()){
            node->setNext(new Bouquet(plants[i], greenhouse,false));  
            greenhouse->remove(plants[i]);
            node = node->getNext();
            node->incPrice(plants[i]->getPrice());
            i++;
        }
        else{
            node = nullptr;
        }
    }

    return bouquet;
}

Product* BouquetBuilder::setContainer(Product* product){
    if(product->getisMain()){
        product->incPrice(rand() % (12 - 5 + 1) + 5);
        product->setContainer("Bouquet Head Container");
    }
    else
    product->setContainer("");

    return product;
}

Product* BouquetBuilder::getProduct(){

    return setContainer(addPlant());
}

//BasicBuilder
BasicBuilder::BasicBuilder(std::vector<Plant*> plants, GardenComponent* greenhouse) : Bob(plants, greenhouse) {
    if(plants.size() > 1){
        std::logic_error("Basic Builder can only take 1 plant");
    }
    else{
        this->plants.push_back(plants[0]);
    }

}

Product* BasicBuilder::addPlant(){
    Product* product = new Product(plants[0],greenhouse,true);
    greenhouse->remove(plants[0]);
    return product;
}

Product* BasicBuilder::addSoil(Product* product){
    product->incPrice(rand() % (15 - 5 + 1) + 5);
    product->setSoil("Basic Soil");
    return product;
}


Product* BasicBuilder::setContainer(Product* product){
    product->incPrice(rand() % (20 - 5 + 1) + 5);
    product->setContainer("Basic Container");
    return product;
}

Product* BasicBuilder::getProduct(){
    return setContainer(addSoil(addPlant()));
}

/////////////////PRODUCT
void Product::setPlant(Plant* p){ 
            if(plant){
                delete plant;
            }
            plant = new Plant(*p);
           
        }


void Product::setSoil(const std::string& s){
        soil = s;
        Inventory.useItem(InventoryCategory::SOIL, s, 1);
        }

        void Product::setContainer(const std::string& c){
            container = c;
            Inventory.useItem(InventoryCategory::CONTAINER, c, 1);
        }

        void Product::setCard(const std::string& c){
            card = c;
            Inventory.useItem(InventoryCategory::CARD, c, 1);
        }

        void Product::setWrapping(const std::string& w){
            wrapping = w;
            Inventory.useItem(InventoryCategory::WRAPPER, w, 1);
        }

float Bouquet::getPrice(){
    if (bouquet->getNext() != nullptr) {
        return price + bouquet->getNext()->getPrice();
    } else {
        return price;
    }
}

//Decorator
Decorator::Decorator(Product* component): Product(component->getPlant(), nullptr, component->getisMain()) {

    if (component && component->getPlant()) {
        this->plant = new Plant(*component->getPlant());
        this->isMain = component->getisMain();
    } else {
        this->plant = nullptr;
    }
}