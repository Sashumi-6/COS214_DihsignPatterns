/**
 * @file product.cpp
 * @brief Implements product builders, decorator extensions, and helpers.
 */
#include "../headers/productBuilder.h"
#include <stdexcept>
#include <cstdlib> // for rand
#include <utility>


/**
 * @brief Constructs a bouquet builder with the plants and greenhouse context.
 */
BouquetBuilder::BouquetBuilder(std::vector<Plant*> plants, GardenComponent* greenhouse)
    : Bob(std::move(plants), greenhouse) {}

/**
 * @brief Builds the bouquet chain by linking supplied plants.
 */
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

/**
 * @brief Applies appropriate container pricing for bouquet products.
 */
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

/**
 * @brief Retrieves the finished bouquet product.
 */
Product* BouquetBuilder::getProduct() {
    Product* p = addPlant();
    return setContainer(p);
}




/**
 * @brief Constructs a basic builder enforcing single-plant usage.
 */
BasicBuilder::BasicBuilder(std::vector<Plant*> plants, GardenComponent* greenhouse)
    : Bob(std::move(plants), greenhouse) {

    if (plants.size() > 1) {
        throw std::logic_error("Basic Builder can only take 1 plant");
    }
}

/**
 * @brief Adds the lone plant to the basic product and updates price.
 */
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

/**
 * @brief Adds default soil and price adjustment to the product.
 */
Product* Bob::addSoil(Product* product) {
    if (!product) return nullptr;
    product->incPrice(rand() % (15 - 5 + 1) + 5);
    product->setSoil("Basic Soil");
    return product;
}

/**
 * @brief Sets a simple container for the basic product.
 */
Product* BasicBuilder::setContainer(Product* product) {
    if (!product) return nullptr;
    product->incPrice(rand() % (20 - 5 + 1) + 5);
    product->setContainer("Basic Container");
    return product;
}

/**
 * @brief Returns the fully constructed basic product.
 */
Product* BasicBuilder::getProduct() {
    return setContainer(addSoil(addPlant()));
}




/**
 * @brief Replaces the product's plant with a cloned version of the supplied plant.
 */
void Product::setPlant(Plant* p) { 
    if (plant) {
        delete plant;
    }
    plant = new Plant(*p);
}

/**
 * @brief Applies soil selection and reduces inventory accordingly.
 */
void Product::setSoil(const std::string& s) {
    soil = s;
    
     inventory.useItem(InventoryCategory::SOIL, s, 1);
}

/**
 * @brief Applies container selection and reduces inventory accordingly.
 */
void Product::setContainer(const std::string& c) {
    container = c;
  
     inventory.useItem(InventoryCategory::CONTAINER, c, 1);
}

/**
 * @brief Applies card selection and reduces inventory accordingly.
 */
void Product::setCard(const std::string& c) {
    card = c;
     inventory.useItem(InventoryCategory::CARD, c, 1);
}

/**
 * @brief Applies wrapping selection and reduces inventory accordingly.
 */
void Product::setWrapping(const std::string& w) {
    wrapping = w;
     inventory.useItem(InventoryCategory::WRAPPER, w, 1);
}




/**
 * @brief Calculates the total price of the bouquet chain.
 */
float Bouquet::getPrice() {
    if (bouquet && bouquet->getNext() != nullptr) {
        return price + bouquet->getNext()->getPrice();
    } else {
        return price;
    }
}




/**
 * @brief Constructs a decorator around an existing product component.
 */
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

/**
 * @brief Clears any plants still owned by the builder on destruction.
 */
Bob::~Bob() {
    // Ownership of plants is transferred to constructed Products/Bouquets.
    plants.clear();
}
