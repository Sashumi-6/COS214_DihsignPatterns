// product_tests.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/productBuilder.h"
#include "../headers/garden.h"
#include "../headers/plant.h"
#include "../headers/doctest.h"
#include "../headers/productBuilder.h"
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <vector>
#include <memory>

TEST_CASE("Product: setters, getters, and price operations") {
    WaterLossStrategy* water = new LowWaterLoss();
    SunlightStrategy* sunlight = new LowSunlightStrategy();
    PlantState* state = new SeedlingState(nullptr);
    GardenSection greenhouse;
    Plant plant("Rose", 10.0f, water, sunlight, state);
    Product product(&plant, &greenhouse, true);

    product.setSoil("Rich Soil");
    product.setContainer("Glass Pot");
    product.setCard("Happy Birthday");
    product.setWrapping("Gold Foil");
    product.incPrice(15.5f);

    CHECK_EQ(product.getSoil(), "Rich Soil");
    CHECK_EQ(product.getContainer(), "Glass Pot");
    CHECK_EQ(product.getCard(), "Happy Birthday");
    CHECK_EQ(product.getWrapping(), "Gold Foil");
    CHECK_EQ(product.getPrice(), doctest::Approx(15.5f));
    CHECK_EQ(product.getName(), "Rose");

    // Replace plant
     WaterLossStrategy* newwater = new LowWaterLoss();
    SunlightStrategy* newsunlight = new LowSunlightStrategy();
    PlantState* newstate = new SeedlingState(nullptr);
    Plant newPlant("Tulip", 7.0f, newwater, newsunlight, newstate);
    product.setPlant(&newPlant);
    CHECK_EQ(product.getPlant()->getName(), "Tulip");
}

TEST_CASE("BouquetBuilder: builds bouquet and sets container") {
    GardenSection greenhouse;
    WaterLossStrategy* water = new LowWaterLoss();
    SunlightStrategy* sunlight = new LowSunlightStrategy();
    PlantState* state = new SeedlingState(nullptr);
    WaterLossStrategy* newwater = new LowWaterLoss();
    SunlightStrategy* newsunlight = new LowSunlightStrategy();
    PlantState* newstate = new SeedlingState(nullptr);
     WaterLossStrategy* moguswater = new LowWaterLoss();
    SunlightStrategy* mogussunlight = new LowSunlightStrategy();
    PlantState* mogusstate = new SeedlingState(nullptr);
    std::vector<Plant*> plants = {
        new Plant("Daisy", 3.0f, water, sunlight, state),
        new Plant("Sunflower", 5.0f, newwater, newsunlight, newstate),
        new Plant("Lily", 2.0f, moguswater, mogussunlight, mogusstate)
    };

    BouquetBuilder builder(plants, &greenhouse);
    Product* product = builder.getProduct();

    REQUIRE(product != nullptr);
    CHECK(product->getPrice() >= 10.0f);  // Sum + container price
    CHECK_EQ(product->getContainer(), "Bouquet Container");

    delete product;
}

TEST_CASE("BouquetBuilder: handles empty vector safely") {
    GardenSection greenhouse;
    std::vector<Plant*> plants;

    BouquetBuilder builder(plants, &greenhouse);
    CHECK_EQ(builder.addPlant(), nullptr);
    CHECK_EQ(builder.setContainer(nullptr), nullptr);
}

TEST_CASE("BasicBuilder: throws when initialized with more than one plant") {
    WaterLossStrategy* water = new LowWaterLoss();
    SunlightStrategy* sunlight = new LowSunlightStrategy();
    PlantState* state = new SeedlingState(nullptr);
    WaterLossStrategy* newwater = new LowWaterLoss();
    SunlightStrategy* newsunlight = new LowSunlightStrategy();
    PlantState* newstate = new SeedlingState(nullptr);
    GardenSection greenhouse;
    std::vector<Plant*> plants = {
        new Plant("Rose", 5.0f,water,sunlight,state),
        new Plant("Tulip", 3.0f,newwater,newsunlight,newstate)
    };

    CHECK_THROWS_AS(BasicBuilder(plants, &greenhouse), std::logic_error);
}

TEST_CASE("BasicBuilder: builds single product and applies soil + container") {
    WaterLossStrategy* water = new LowWaterLoss();
    SunlightStrategy* sunlight = new LowSunlightStrategy();
    PlantState* state = new SeedlingState(nullptr);
    GardenSection greenhouse;
    std::vector<Plant*> plants = { new Plant("Sunflower", 8.0f, water, sunlight, state) };
    BasicBuilder builder(plants, &greenhouse);

    Product* product = builder.getProduct();
    REQUIRE(product != nullptr);

    CHECK_EQ(product->getSoil(), "Basic Soil");
    CHECK_EQ(product->getContainer(), "Basic Container");
    CHECK(product->getPrice() > 0.0f);

    delete product;
}

TEST_CASE("Bouquet: recursive price calculation works correctly") {
    WaterLossStrategy* water = new LowWaterLoss();
    SunlightStrategy* sunlight = new LowSunlightStrategy();
    PlantState* state = new SeedlingState(nullptr);
    WaterLossStrategy* newwater = new LowWaterLoss();
    SunlightStrategy* newsunlight = new LowSunlightStrategy();
    PlantState* newstate = new SeedlingState(nullptr);
    GardenSection greenhouse;
    Plant p1("A", 5.0f, water, sunlight, state), p2("B", 6.0f, newwater, newsunlight, newstate);
    Bouquet b1(&p1, &greenhouse, true);
    Bouquet b2(&p2, &greenhouse, false);

    b1.incPrice(10.0f);
    b2.incPrice(20.0f);
    b1.setNext(&b2);

    CHECK_EQ(b1.getPrice(), 30.0f);
    CHECK_EQ(b2.getPrice(), 20.0f);
}

TEST_CASE("Decorator: copies plant and maintains isMain flag") {
    WaterLossStrategy* water = new LowWaterLoss();
    SunlightStrategy* sunlight = new LowSunlightStrategy();
    PlantState* state = new SeedlingState(nullptr);
    GardenSection greenhouse;
    Plant plant("Decorated", 8.0f, water, sunlight, state);
    Product base(&plant, &greenhouse, true);

    Decorator decorator(&base);

    REQUIRE(decorator.getPlant() != nullptr);
    CHECK_EQ(decorator.getPlant()->getName(), "Decorated");
    CHECK_EQ(decorator.getisMain(), true);
}

TEST_CASE("Decorator: handles nullptr safely") {
    Decorator d(nullptr);
    CHECK(d.getPlant() == nullptr);
}

TEST_CASE("Bob destructor: safely deletes all allocated plants") {
    GardenSection greenhouse;
    WaterLossStrategy* water = new LowWaterLoss();
    SunlightStrategy* sunlight = new LowSunlightStrategy();
    PlantState* state = new SeedlingState(nullptr);
    WaterLossStrategy* newwater = new LowWaterLoss();
    SunlightStrategy* newsunlight = new LowSunlightStrategy();
    PlantState* newstate = new SeedlingState(nullptr);
    std::vector<Plant*> plants = {
        new Plant("Z1", 1.0f, water, sunlight, state),
        new Plant("Z2", 2.0f, newwater, newsunlight, newstate)
    };

    class DummyBob : public Bob {
    public:
        DummyBob(std::vector<Plant*> p, GardenSection* g) : Bob(p, g) {}
        Product* addPlant() override { return nullptr; }
        Product* setContainer(Product* p) override { return p; }
        Product* getProduct() override { return nullptr; }
    };

    DummyBob* bob = new DummyBob(plants, &greenhouse);
    CHECK_NOTHROW(delete bob);
}
