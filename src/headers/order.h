/**
 * @file order.h
 * @brief Declares the Order aggregate responsible for customer purchases.
 *
 * Orders manage product lists, payment state, and utilize builders to
 * assemble requested products from greenhouse resources.
 */
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "productRequest.h"

class GardenComponent;
class Product;
class Cashier;

/** @brief Lifecycle state of a customer order. */
enum OrderStatus{
    PENDING,
    PROCESSING,
    COMPLETED,
    CANCELLED
};
/**
 * @brief Represents a customer order composed of requested products.
 */
class Order {
    public:
        /**
         * @brief Constructs an order tied to a cashier and customer.
         * @param cashier Cashier responsible for fulfillment.
         * @param customerName Name of the customer placing the order.
         */
        Order(Cashier* cashier, std::string customerName);
        /**
         * @brief Adds a product to the order.
         */
        void addProduct(Product* p);
        /**
         * @brief Removes a product from the order.
         */
        void removeProduct(Product* p);
        /**
         * @brief Calculates the total price for the order.
         * @return Aggregate product price.
         */
        double calculateTotal();
        /**
         * @brief Updates the order status.
         * @param s New status value.
         */
        void updateStatus(OrderStatus s);
        /**
         * @brief Finalizes the order by building requested products.
         * @param greenhouse Greenhouse composite for resource lookup.
         */
        void finaliseOrder(GardenComponent* greenhouse);
        /**
         * @brief Checks whether the order has been paid.
         * @return True if payment received.
         */
        bool isPaid();
        /**
         * @brief Toggles the payment state.
         */
        void togglePaymentStatus();
        /**
         * @brief Generates a human-readable order summary.
         */
        std::string orderDetails();
        /**
         * @brief Returns the number of products ordered.
         */
        int getProductCount();
        /**
         * @brief Retrieves the most recently added product.
         */
        Product* getProduct();
        /**
         * @brief Adds a product request to be processed by the builder.
         */
        void addRequest(const ProductRequest& r);

    private:
        /** Cached total price for current items. */
        double totalPrice;
        /** Collection of products included in the order. */
        std::vector<Product*> orderedProducts;
        /** Unique identifier for the order. */
        int orderId;
        /** Name of the customer associated with the order. */
        std::string customerName;
        /** Current status of the order. */
        OrderStatus status;
        /** Tracks whether the customer has paid. */
        bool paymentReveived;
        /** Cashier reference used to construct products via builder. */
        Cashier* cashier;//here because of Builder. Has to have specific builder parsed in
        /** Product requests awaiting construction. */
        std::vector<ProductRequest> requests;
};

#endif
