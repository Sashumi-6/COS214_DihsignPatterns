#ifndef ORDER_H
#define ORDER_H

#include "plant.h"
#include"employee.h"
#include "productBuilder.h"
#include <vector>
#include "frontDesk.h"
class OrderState;
class Product;
class Cashier;
struct ProductRequest;

enum OrderStatus{
    PENDING,
    PROCESSING,
    COMPLETED,
    CANCELLED
};
class Order {
    public:
        Order(Cashier* cashier, std::string customerName);
        void addProduct(Product* p);
        void removeProduct(Product* p);
        double calculateTotal();
        void updateStatus(OrderStatus s);
        void finaliseOrder(GardenComponent* greenhouse);
        bool isPaid();
        void togglePaymentStatus();
        std::string orderDetails();
        int getProductCount();
        Product* getProduct();
        void addRequest(const ProductRequest& r);

    private:
        double totalPrice;
        std::vector<Product*> orderedProducts;
        int orderId;
        std::string customerName;
        OrderStatus status;
        bool paymentReveived;
        Cashier* cashier;//here because of Builder. Has to have specific builder parsed in
        std::vector<ProductRequest> requests;
};

#endif