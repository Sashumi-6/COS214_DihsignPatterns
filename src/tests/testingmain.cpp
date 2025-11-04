// product_tests.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../headers/productBuilder.h"
#include "../headers/garden.h"
#include "../headers/plant.h"
#include "../headers/doctest.h"
#include "../headers/productBuilder.h"
#include "../headers/frontDesk.h"
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <vector>
#include <memory>


TEST_CASE("WaterLoss strategies return correct values") {
    LowWaterLoss low;
    MedWaterLoss med;
    HighWaterLoss high;

    CHECK(low.loseWater() == doctest::Approx(0.1));
    CHECK(med.loseWater() == doctest::Approx(0.25));
    CHECK(high.loseWater() == doctest::Approx(0.35));
}


TEST_CASE("Sunlight strategies return correct locations") {
    LowSunlightStrategy low;
    MedSunlightStrategy med;
    HighSunlightStrategy high;

    CHECK(low.exposeToSun() == PlantLocation::INSIDE);
    CHECK(med.exposeToSun() == PlantLocation::GREENHOUSE);
    CHECK(high.exposeToSun() == PlantLocation::OUTSIDE);
}

TEST_CASE("Plant transitions from Seedling to Mature to Dead through growth") {
    auto* waterLoss = new LowWaterLoss();
    auto* sunlight = new LowSunlightStrategy();
    auto* state = new SeedlingState(nullptr);

    Plant plant("Rose", 15.0, waterLoss, sunlight, state);
    state->setPlant(&plant);

    CHECK_FALSE(plant.canSell()); // Seedling can't sell

    plant.grow();  // should become Mature
    CHECK(plant.canSell()); // Mature can sell

    plant.grow();  // should become Dead
    CHECK_FALSE(plant.canSell()); // Dead can't sell
}

TEST_CASE("Plant dies if overwatered") {
    auto* waterLoss = new LowWaterLoss();
    auto* sunlight = new LowSunlightStrategy();
    auto* state = new SeedlingState(nullptr);

    Plant plant("Tulip", 12.0, waterLoss, sunlight, state);
    state->setPlant(&plant);

    // Add too much water
    plant.addWater(2.0);

    CHECK_FALSE(plant.canSell()); // should be DeadState
}

TEST_CASE("Plant dies if water level drops below 0") {
    auto* waterLoss = new HighWaterLoss();
    auto* sunlight = new HighSunlightStrategy();
    auto* state = new SeedlingState(nullptr);

    Plant plant("Cactus", 8.0, waterLoss, sunlight, state);
    state->setPlant(&plant);

    // Apply heavy water loss repeatedly
    plant.applyWaterLoss();
    plant.applyWaterLoss();
    plant.applyWaterLoss();

    CHECK_FALSE(plant.canSell()); // Dead state expected
}

TEST_CASE("Plant grows only if water level >= 0.5 and age >= 5") {
    auto* waterLoss = new LowWaterLoss();
    auto* sunlight = new LowSunlightStrategy();
    auto* state = new SeedlingState(nullptr);

    Plant plant("Fern", 10.0, waterLoss, sunlight, state);
    state->setPlant(&plant);

    // This won't trigger growth yet
    plant.tryGrow();
    CHECK_FALSE(plant.canSell());

    // Simulate conditions
    plant.addWater(0.5);
    for (int i = 0; i < 3; ++i) plant.grow(); // increase age

    // Now try to grow again
    plant.tryGrow();
    CHECK(plant.canSell()); // should now be Mature
}

TEST_CASE("ProductBuilder creates correct Products using BasicBuilder and BouquetBuilder") {
    // --- Setup dependencies ---
    GardenComponent* greenhouse = new GardenSection();
    
    std::vector<Plant*> basicPlants = { new Plant("Aloe", 25.0, new LowWaterLoss(), new LowSunlightStrategy(), new SeedlingState(nullptr)) };
    std::vector<Plant*> bouquetPlants = {
        new Plant("Rose", 20.0, new LowWaterLoss(), new LowSunlightStrategy(), new SeedlingState(nullptr)),
        new Plant("Tulip", 15.0, new LowWaterLoss(), new LowSunlightStrategy(), new SeedlingState(nullptr)),
        new Plant("Lily", 25.0, new LowWaterLoss(), new LowSunlightStrategy(), new SeedlingState(nullptr))
    };

    // for (auto* p : basicPlants) p->getState()->setPlant(p);
    // for (auto* p : bouquetPlants) p->getState()->setPlant(p);

    // --- Test BasicBuilder ---
    BasicBuilder basicBuilder(basicPlants, greenhouse);
    Product* basicProduct = basicBuilder.getProduct();

    CHECK(basicProduct != nullptr);
    CHECK(basicProduct->getPlant() != nullptr);
    CHECK(basicProduct->getContainer() == "Basic Container");
    CHECK(basicProduct->getSoil() == "Basic Soil");
    CHECK(basicProduct->getPrice() > 25.0); // plant price + container + soil

    // --- Test BouquetBuilder ---
    BouquetBuilder bouquetBuilder(bouquetPlants, greenhouse);
    Product* bouquet = bouquetBuilder.getProduct();

    CHECK(bouquet != nullptr);
    CHECK(bouquet->getPlant() != nullptr);
    CHECK(bouquet->getisMain() == true);
    CHECK(bouquet->getContainer() == "Bouquet Container");
    CHECK(bouquet->getPrice() >= 20.0);

    // --- Test Decorators ---
    Product* cardDecorated = new CardDecorator(basicProduct, "Happy Birthday");
    Product* wrappedDecorated = new WrappingPaperDecorator(cardDecorated, "Floral Wrap");

    wrappedDecorated->setCard("Happy Birthday");
    wrappedDecorated->setWrapping("Floral Wrap");

    CHECK(wrappedDecorated->getCard() == "Happy Birthday");
    CHECK(wrappedDecorated->getWrapping() == "Floral Wrap");

    // --- Cleanup ---
    delete wrappedDecorated;
    delete bouquet;
    delete greenhouse;
}
