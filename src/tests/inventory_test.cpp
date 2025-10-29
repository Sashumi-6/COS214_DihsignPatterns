#include <gtest/gtest.h>
#include "../headers/inventory.h"

TEST(Inventory , Add_Stock_Wrappers) {
    Inventory inv(nullptr) ;
    inv.addStock(InventoryCategory::WRAPPER , "Testing Wrapper" , 10) ;
    EXPECT_EQ(inv.itemExists(InventoryCategory::WRAPPER, "Testing Wrapper") , true) ;
    EXPECT_EQ(inv.getQuantity(InventoryCategory::WRAPPER, "Testing Wrapper") , 10) ;
}