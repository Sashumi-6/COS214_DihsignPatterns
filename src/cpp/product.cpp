#include "../headers/productBuilder.h"
#include <stdexcept>
#include <cstdlib> // for rand



BouquetBuilder::BouquetBuilder(std::vector<Plant*> plants, GardenComponent* greenhouse)
    : Bob(plants, greenhouse) {
    this->plants = plants;
}

Product* BouquetBuilder::addPlant() {
  
    if (plants.empty()) return nullptr;

    Bouquet* bouquet = new Bouquet(plants[0], greenhouse, true);
    bouquet->incPrice(plants[0]->getPrice());
    greenhouse->remove(plants[0]);

    Bouquet* node = bouquet;
    int i = 1;

    while (node != nullptr) {
        if (node->getNext() == nullptr && i < static_cast<int>(plants.size())) {
            node->setNext(new Bouquet(plants[i], greenhouse, false));  
            greenhouse->remove(plants[i]);
            node = node->getNext();
            node->incPrice(plants[i]->getPrice());
            i++;
        } else {
            node = nullptr;
        }
    }

    return bouquet;
}

Product* BouquetBuilder::setContainer(Product* product) {
    if (!product) return nullptr;

    if (product->getisMain()) {
        product->incPrice(rand() % (12 - 5 + 1) + 5);
        product->setContainer("Bouquet Container");
    } else {
        product->setContainer("");
    }

    return product;
}

Product* BouquetBuilder::getProduct() {
    Product* p = addPlant();
    return setContainer(p);
}




BasicBuilder::BasicBuilder(std::vector<Plant*> plants, GardenComponent* greenhouse)
    : Bob(plants, greenhouse) {

    if (plants.size() > 1) {
        throw std::logic_error("Basic Builder can only take 1 plant");
    }

    if (!plants.empty()) {
        this->plants.push_back(plants[0]);
    }
}

Product* BasicBuilder::addPlant() {
    if (plants.empty()) return nullptr;
    Product* product = new Product(plants[0], greenhouse, true);
    greenhouse->remove(plants[0]);
    return product;
}

Product* Bob::addSoil(Product* product) {
    if (!product) return nullptr;
    product->incPrice(rand() % (15 - 5 + 1) + 5);
    product->setSoil("Basic Soil");
    return product;
}

Product* BasicBuilder::setContainer(Product* product) {
    if (!product) return nullptr;
    product->incPrice(rand() % (20 - 5 + 1) + 5);
    product->setContainer("Basic Container");
    return product;
}

Product* BasicBuilder::getProduct() {
    return setContainer(addSoil(addPlant()));
}




void Product::setPlant(Plant* p) { 
    if (plant) {
        delete plant;
    }
    plant = new Plant(*p);
}

void Product::setSoil(const std::string& s) {
    soil = s;
    
     Inventory.useItem(InventoryCategory::SOIL, s, 1);
}

void Product::setContainer(const std::string& c) {
    container = c;
  
     Inventory.useItem(InventoryCategory::CONTAINER, c, 1);
}

void Product::setCard(const std::string& c) {
    card = c;
     Inventory.useItem(InventoryCategory::CARD, c, 1);
}

void Product::setWrapping(const std::string& w) {
    wrapping = w;
     Inventory.useItem(InventoryCategory::WRAPPER, w, 1);
}




float Bouquet::getPrice() {
    if (bouquet && bouquet->getNext() != nullptr) {
        return price + bouquet->getNext()->getPrice();
    } else {
        return price;
    }
}




Decorator::Decorator(Product* component)
    : Product(component ? component->getPlant() : nullptr, nullptr,
              component ? component->getisMain() : false), component(component) {

    if (component && component->getPlant()) {
        this->soil = component->getSoil();
        this->container = component->getContainer();
        this->card = component->getCard();
        this->wrapping = component->getWrapping();
    } else {
        this->plant = nullptr;
    }
}

Bob::~Bob() {
    // No dynamic memory to clean up in Bob itself
    for (auto plant : plants) {
        if(plant){
            delete plant;
            plant = nullptr;
        }
    }
}
