#include "../headers/productBuilder.h"
#include <stdexcept>
#include <cstdlib> // for rand
#include <utility>



BouquetBuilder::BouquetBuilder(std::vector<Plant*> plants, GardenComponent* greenhouse)
    : Bob(std::move(plants), greenhouse) {}

Product* BouquetBuilder::addPlant() {
  
    if (plants.empty()) return nullptr;

    Plant* first = plants[0];
    Bouquet* bouquet = new Bouquet(first, greenhouse, true);
    bouquet->incPrice(first->getPrice());
    greenhouse->remove(first);
    plants[0] = nullptr;

    Bouquet* node = bouquet;
    int i = 1;

    while (node != nullptr) {
        if (node->getNext() == nullptr && i < static_cast<int>(plants.size())) {
            Plant* current = plants[i];
            node->setNext(new Bouquet(current, greenhouse, false));  
            greenhouse->remove(current);
            node = node->getNext();
            node->incPrice(current->getPrice());
            plants[i] = nullptr;
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
    : Bob(std::move(plants), greenhouse) {

    if (plants.size() > 1) {
        throw std::logic_error("Basic Builder can only take 1 plant");
    }
}

Product* BasicBuilder::addPlant() {
    if (plants.empty()) return nullptr;
    Plant* source = plants[0];
    Product* product = new Product(source, greenhouse, true);
    if (source) {
        product->incPrice(source->getPrice());
    }
    greenhouse->remove(source);
    plants[0] = nullptr;
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
    
     inventory.useItem(InventoryCategory::SOIL, s, 1);
}

void Product::setContainer(const std::string& c) {
    container = c;
  
     inventory.useItem(InventoryCategory::CONTAINER, c, 1);
}

void Product::setCard(const std::string& c) {
    card = c;
     inventory.useItem(InventoryCategory::CARD, c, 1);
}

void Product::setWrapping(const std::string& w) {
    wrapping = w;
     inventory.useItem(InventoryCategory::WRAPPER, w, 1);
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
    // Ownership of plants is transferred to constructed Products/Bouquets.
    plants.clear();
}
