#ifndef ORDER_H
#define ORDER_H

#include "plant.h"
#include <vector>
class OrderState;
class Product;

class Order {
    public:
        Order(std::string customerName, std::string productSpecs);
        void addProduct(Product* p);
        void removeProduct(Product* p);
        double calculateTotal();
        void updateStatus(OrderStatus s);
        void finaliseOrder();
        bool isPaid();
        void togglePaymentStatus();
        std::string orderDetails();
        int getProductCount();
        Product* getProduct();

    private:
        double totalPrice;
        std::vector<Product*> orderedProducts;
        int orderId;
        std::string customerName;
        OrderStatus status;
        bool paymentReveived;
};

enum OrderStatus{
    PENDING,
    PROCESSING,
    COMPLETED,
    CANCELLED
};

#endif