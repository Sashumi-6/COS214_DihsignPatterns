/**
 * @file productBuilder.h
 * @brief Declares product construction classes leveraging the builder pattern.
 *
 * Provides product abstractions, concrete builders, and decorators used to
 * assemble bouquets and packaged plant products.
 */
#ifndef PRODUCTBUILDER_H
#define PRODUCTBUILDER_H

#include <vector>
#include <string>
#include "plant.h"
#include "inventory.h"
#include "garden.h"

class GardenComponent; // forward declaration for pointer usage in Product
class Product;  // forward declaration for pointer usage in Bob

/**
 * @brief Base class representing a sellable plant product.
 */
class Product{
protected:
    /** Plant forming the centerpiece of the product. */
    Plant* plant;
    /** Soil selection used for the arrangement. */
    std::string soil;
    /** Container selected for the product. */
    std::string container;
    /** Optional card message. */
    std::string card;
    /** Optional wrapping material. */
    std::string wrapping;
    Inventory inventory; // CHANGED: lowercase 'i' to avoid naming conflict
    /** Total price of the product. */
    float price;
    /** Flags whether this is the primary item in a bouquet chain. */
    bool isMain;

public:
    /**
     * @brief Retrieves the product display name.
     */
    std::string getName() const { 
        return plant ? plant->getName() : "Unknown Product"; 
    }
    
    virtual ~Product(){
        if (plant) {
            delete plant;
            plant = nullptr;
        }
    }
    
    /**
     * @brief Constructs a product from a plant within a greenhouse context.
     * @param plant Core plant for the product.
     * @param greenhouse Greenhouse composite for inventory interaction.
     * @param isMain Indicates if this is the main product in a chain.
     */
    Product(Plant* plant, GardenComponent* greenhouse, bool isMain) 
        : plant(plant), inventory(greenhouse), isMain(isMain) {
        soil = "";
        container = "";
        card = "";
        wrapping = "";
        price = 0;
    }

    /**
     * @brief Indicates if the product is the main bouquet component.
     */
    bool getisMain() const { return isMain; }

    /**
     * @brief Replaces the product's plant.
     * @param p New plant pointer.
     */
    void setPlant(Plant* p);

    // accessor to allow safe access to the plant from other objects
    /**
     * @brief Provides read-only access to the plant.
     */
    Plant* getPlant() const { return plant; }
    
    /**
     * @brief Sets the soil description.
     */
    void setSoil(const std::string& s);
    /**
     * @brief Sets the container description.
     */
    void setContainer(const std::string& c);
    /**
     * @brief Sets the card message.
     */
    void setCard(const std::string& c);
    /**
     * @brief Sets the wrapping description.
     */
    void setWrapping(const std::string& w);

    /**
     * @brief Retrieves the soil option assigned to the product.
     */
    std::string getSoil() const { return soil; }
    /**
     * @brief Retrieves the container option assigned to the product.
     */
    std::string getContainer() const { return container; }
    /**
     * @brief Returns the card message, if any.
     */
    std::string getCard() const { return card; }
    /**
     * @brief Returns the wrapping option, if any.
     */
    std::string getWrapping() const { return wrapping; }

    /**
     * @brief Returns the total price of the product.
     */
    float getPrice() const { return price; }
    /**
     * @brief Increases the price by a given amount.
     * @param amount Increment applied to the price.
     */
    void incPrice(float amount) { price += amount; }
};

/**
 * @brief Abstract builder responsible for constructing products.
 */
class Bob {
public:
    /**
     * @brief Stores plants and greenhouse reference for construction.
     * @param plant Collection of plants for the product.
     * @param greenhouse Greenhouse used for inventory access.
     */
    Bob(std::vector<Plant*> plant, GardenComponent* greenhouse) 
        : plants(plant), greenhouse(greenhouse) {};
    /**
     * @brief Adds a plant to the product.
     */
    virtual Product* addPlant() = 0;
    /**
     * @brief Applies soil to a product instance.
     * @param product Product to modify.
     */
    Product* addSoil(Product* product);
    /**
     * @brief Chooses the container for the product.
     */
    virtual Product* setContainer(Product* product) = 0;
    /**
     * @brief Retrieves the fully constructed product.
     */
    virtual Product* getProduct() = 0;
    virtual ~Bob();
    
protected:
    /** Plants available for inclusion in the product. */
    std::vector<Plant*> plants;
    /** Greenhouse context used during construction. */
    GardenComponent* greenhouse;
};

/**
 * @brief Concrete builder producing bouquet products.
 */
class BouquetBuilder : public Bob {
public:
    BouquetBuilder(std::vector<Plant*> plant, GardenComponent* greenhouse);
    /**
     * @brief Constructs the bouquet chain from the supplied plants.
     */
    Product* addPlant() override;
    /**
     * @brief Applies bouquet-specific container selection.
     */
    Product* setContainer(Product* product) override;
    /**
     * @brief Returns the completed bouquet product.
     */
    Product* getProduct();
};

/**
 * @brief Concrete builder producing basic potted products.
 */
class BasicBuilder : public Bob {
public:
    BasicBuilder(std::vector<Plant*> plants, GardenComponent* greenhouse);
    /**
     * @brief Builds the base product using a single plant.
     */
    Product* addPlant();
    /**
     * @brief Chooses a basic container option.
     */
    Product* setContainer(Product* product) override;
    /**
     * @brief Returns the assembled basic product.
     */
    Product* getProduct();
};

/**
 * @brief Product used as a base for bouquet compositions.
 */
class BouquetProduct : public Product {
public:
    BouquetProduct(Plant* plant, GardenComponent* greenhouse, bool isMain) 
        : Product(plant, greenhouse, isMain) {}
};

/**
 * @brief Represents a node in a bouquet chain, aggregating multiple plants.
 */
class Bouquet : public BouquetProduct {
public:
    Bouquet(Plant* plant, GardenComponent* greenhouse, bool isMain) 
        : BouquetProduct(plant, greenhouse, isMain), bouquet(nullptr) {}
        
    /**
     * @brief Returns the next bouquet element in the chain.
     */
    Bouquet* getNext() { return bouquet; }
    /**
     * @brief Sets the next bouquet element.
     */
    void setNext(Bouquet* bouquet) { this->bouquet = bouquet; }
    /**
     * @brief Calculates the cumulative price for the bouquet chain.
     */
    float getPrice();
        
private:
    /** Next bouquet node for linked composition. */
    Bouquet* bouquet;
};

/**
 * @brief Decorator base for augmenting products with optional features.
 */
class Decorator : public Product {
private:
    /** Wrapped product component. */
    Product* component;
public:
    /**
     * @brief Binds the decorator to an existing product.
     * @param component Component to decorate.
     */
    Decorator(Product* component);
};

/**
 * @brief Decorator adding card customizations to products.
 */
class CardDecorator : public Decorator {
public:
    CardDecorator(Product* component, std::string cardString) 
        : Decorator(component) {
        setCard(cardString);
    }
};

/**
 * @brief Decorator adding wrapping paper to products.
 */
class WrappingPaperDecorator : public Decorator {
public:
    WrappingPaperDecorator(Product* component, std::string wrappingString) 
        : Decorator(component) {
        setWrapping(wrappingString);
    }
};

#endif
