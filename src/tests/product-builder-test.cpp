#include "gtest/gtest.h"
#include "../headers/productBuilder.h"
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// Mock classes for dependencies
class MockGreenhouse : public GardenComponent {
public:
    vector<Plant*> removed;
    void remove(Plant* p) override { removed.push_back(p); }
};

class MockInventory {
public:
    int soilUsed = 0;
    int containerUsed = 0;
    int cardUsed = 0;
    int wrapperUsed = 0;

    void useItem(InventoryCategory cat, const string& name, int count) {
        switch (cat) {
            case InventoryCategory::SOIL: soilUsed += count; break;
            case InventoryCategory::CONTAINER: containerUsed += count; break;
            case InventoryCategory::CARD: cardUsed += count; break;
            case InventoryCategory::WRAPPER: wrapperUsed += count; break;
        }
    }
};

// Global mock Inventory
MockInventory mockInventory;
InventoryClass Inventory = mockInventory; // Replace global Inventory

// Utility plant creation
Plant* makePlant(const string& name = "Rose") {
    return new Plant(name);
}

//
// -------- TESTS --------
//

// --- BouquetBuilder ---

TEST(BouquetBuilderTest, AddPlantCreatesLinkedBouquet) {
    MockGreenhouse greenhouse;
    vector<Plant*> plants = { makePlant("A"), makePlant("B"), makePlant("C") };
    BouquetBuilder builder(plants, &greenhouse);

    Product* bouquet = builder.addPlant();
    ASSERT_NE(bouquet, nullptr);

    Bouquet* bq = dynamic_cast<Bouquet*>(bouquet);
    ASSERT_NE(bq, nullptr);
    EXPECT_EQ(greenhouse.removed.size(), 2);  // both A and B removed
}

TEST(BouquetBuilderTest, SetContainerAssignsCorrectName) {
    MockGreenhouse greenhouse;
    vector<Plant*> plants = { makePlant("Lily") };
    BouquetBuilder builder(plants, &greenhouse);

    Product* p = new Product(plants[0], &greenhouse);
    builder.setContainer(p);

    EXPECT_EQ(p->getContainer(), "Bouquet Container");
}

// --- BasicBuilder ---

TEST(BasicBuilderTest, ThrowsIfMoreThanOnePlant) {
    MockGreenhouse greenhouse;
    vector<Plant*> plants = { makePlant("Rose"), makePlant("Tulip") };

    EXPECT_THROW({
        BasicBuilder builder(plants, &greenhouse);
    }, logic_error);
}

TEST(BasicBuilderTest, AddsPlantAndRemovesFromGreenhouse) {
    MockGreenhouse greenhouse;
    vector<Plant*> plants = { makePlant("Orchid") };
    BasicBuilder builder(plants, &greenhouse);

    Product* p = builder.addPlant();
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(greenhouse.removed.size(), 1);
}

TEST(BasicBuilderTest, SetsSoilAndContainer) {
    MockGreenhouse greenhouse;
    vector<Plant*> plants = { makePlant("Daisy") };
    BasicBuilder builder(plants, &greenhouse);

    Product* p = builder.addPlant();
    builder.addSoil(p);
    builder.setContainer(p);

    EXPECT_EQ(p->getSoil(), "Basic Soil");
    EXPECT_EQ(p->getContainer(), "Basic Container");
}

// --- Product ---

TEST(ProductTest, SetPlantReplacesOldPlant) {
    Product p(makePlant("A"), nullptr);
    Plant* newPlant = makePlant("B");
    p.setPlant(newPlant);

    EXPECT_EQ(p.getPlant()->getName(), "B");
}

TEST(ProductTest, SetSoilUsesInventory) {
    Product p(makePlant(), nullptr);
    mockInventory.soilUsed = 0;

    p.setSoil("Rich Soil");
    EXPECT_EQ(p.getSoil(), "Rich Soil");
    EXPECT_EQ(mockInventory.soilUsed, 1);
}

TEST(ProductTest, SetContainerUsesInventory) {
    Product p(makePlant(), nullptr);
    mockInventory.containerUsed = 0;

    p.setContainer("Pot");
    EXPECT_EQ(p.getContainer(), "Pot");
    EXPECT_EQ(mockInventory.containerUsed, 1);
}

// --- Decorator ---

TEST(DecoratorTest, CopiesPlantFromComponent) {
    Product* base = new Product(makePlant("Fern"), nullptr);
    Decorator deco(base);

    ASSERT_NE(deco.getPlant(), nullptr);
    EXPECT_EQ(deco.getPlant()->getName(), "Fern");
}
