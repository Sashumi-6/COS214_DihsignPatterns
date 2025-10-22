#ifndef ORDER_H
#define ORDER_H

#include "plant.h"
class OrderState;
class Product;

class Order {
    public:
        void completeOrder();
        void addProduct(Product* product);

    private:
        Plant* plants;
        float totalCost;
        OrderState* state;

};

class OrderState {

};

class ProcessingState : public OrderState {

};

class CompletedState : public OrderState {

};

#endif