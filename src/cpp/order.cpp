/**
 * @file order.cpp
 * @brief Implements order management and product assembly operations.
 */
#include "../headers/order.h"
#include "../headers/employee.h"
#include "../headers/productBuilder.h"
#include <sstream>
#include <iostream>
/**
 * @brief Initializes an order with a cashier and customer name.
 */
Order::Order(Cashier* c, std::string name)
    : cashier(c), customerName(name), totalPrice(0.0), status(PENDING), paymentReveived(false) 
{}


/**
 * @brief Adds a product to the order and updates totals.
 */
void Order::addProduct(Product* p) {
    if(p) {
        orderedProducts.push_back(p);
        totalPrice += p->getPrice(); // TODO check function name
    }
}

/**
 * @brief Removes a product from the order if present.
 */
void Order::removeProduct(Product* p) {
    for(auto it = orderedProducts.begin(); it != orderedProducts.end(); ++it) {
        if(*it == p) {
            totalPrice -= p->getPrice();
            orderedProducts.erase(it);
            break;
        }
    }
}

// ================= Calculate Total =================
/**
 * @brief Recalculates the total cost of all products.
 */
double Order::calculateTotal() {
    totalPrice = 0.0;
    for(auto p : orderedProducts) {
        totalPrice += p->getPrice();
    }
    return totalPrice;
}

/**
 * @brief Updates the order's status state.
 */
void Order::updateStatus(OrderStatus s) {
    status = s;
}

/**
 * @brief Builds requested products and adds them to the order.
 */
void Order::finaliseOrder(GardenComponent* greenhouse) {
    for(const auto& req : requests) {
        Product* product = cashier->construct(req, greenhouse);
        if(product) {
            addProduct(product);
        }else{
           // TODO error handling for product that couldn't be made
        }
    }
    updateStatus(PROCESSING);
}

/**
 * @brief Stores a product request for later processing.
 */
void Order::addRequest(const ProductRequest& r) {
    requests.push_back(r);
}
// ================= Payment Status =================
/**
 * @brief Reports if the order has been paid.
 */
bool Order::isPaid() {
    return paymentReveived;
}

/**
 * @brief Toggles payment status between paid and unpaid.
 */
void Order::togglePaymentStatus() {
    paymentReveived = !paymentReveived;
}

// ================= Order Details =================
/**
 * @brief Generates a multi-line summary of the order.
 */
std::string Order::orderDetails() {
    std::ostringstream oss;
    oss << "Order for " << customerName << ":\n";
    for(auto p : orderedProducts) {
        oss << "- " << p->getName() << " : $" << p->getPrice() << "\n";
    }
    oss << "Total: $" << calculateTotal() << "\n";
    oss << "Status: ";
    switch(status) {
        case PENDING: oss << "PENDING"; break;
        case PROCESSING: oss << "PROCESSING"; break;
        case COMPLETED: oss << "COMPLETED"; break;
        case CANCELLED: oss << "CANCELLED"; break;
    }
    oss << "\nPayment: " << (paymentReveived ? "PAID" : "NOT PAID") << "\n";
    return oss.str();
}

// ================= Get Product Count / Access =================
/**
 * @brief Returns the number of products currently attached to the order.
 */
int Order::getProductCount() {
    return orderedProducts.size();
}

/**
 * @brief Retrieves the most recently added product.
 */
Product* Order::getProduct() {
    if(!orderedProducts.empty()) {
        return orderedProducts.back(); // returns the last added product
    }
    return nullptr;
}
