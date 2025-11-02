// ...existing code...
#include "gtest/gtest.h"
#include "../headers/productBuilder.h"
#include "../headers/plant.h"
#include "../headers/garden.h"
#include <string>
#include <vector>


static Plant* makePlant(const std::string& name = "Rose", double price = 1.0) {
    return new Plant(name, price,
                     new LowWaterLoss(), new LowSunlightStrategy(),
                     new SeedlingState(nullptr));
}

TEST(BasicBuilderTest, AddsPlantAndKeepsPlantPointer) {
    Plant* p = makePlant("Orchid");
    std::vector<Plant*> plants = { p };

    GardenSection greenhouse;
   
    greenhouse.add(p);

    BasicBuilder builder(plants, &greenhouse);
    Product* product = builder.addPlant();

    ASSERT_NE(product, nullptr);

    ASSERT_EQ(product->getPlant(), p);

    delete product;
    delete p;
}

TEST(BouquetBuilderTest, ReturnsBouquetProduct) {
    const int N = 3;
    std::vector<Plant*> plants;
    plants.reserve(N);
    for (int i = 0; i < N; ++i) plants.push_back(makePlant("B" + std::to_string(i)));

    GardenSection greenhouse;
    for (auto pl : plants) greenhouse.add(pl);

    BouquetBuilder builder(plants, &greenhouse);
    Product* product = builder.addPlant();

    ASSERT_NE(product, nullptr);
    Bouquet* bq = dynamic_cast<Bouquet*>(product);
    ASSERT_NE(bq, nullptr);

    delete product;
    for (auto pl : plants) delete pl;
}

TEST(BouquetBuilderTest, SetContainerAssignsCorrectName) {
    Plant* p = makePlant("Lily");
    GardenSection greenhouse;
    Product prod(p, &greenhouse);

    BouquetBuilder builder(std::vector<Plant*>{p}, &greenhouse);
    builder.setContainer(&prod);

    EXPECT_EQ(prod.getContainer(), "Bouquet Container");

    delete p;
}
// ...existing code...