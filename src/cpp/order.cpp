#include "order.h"
#include <sstream>
#include <iostream>


Order::Order(Cashier* c, std::string name, std::string productSpecs)
    : cashier(c), customerName(name), totalPrice(0.0), status(PENDING), paymentReveived(false) 
{
    //TODO decide format of productSpecs
}


void Order::addProduct(Product* p) {
    if(p) {
        orderedProducts.push_back(p);
        totalPrice += p->getPrice(); // TODO check function name
    }
}

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
double Order::calculateTotal() {
    totalPrice = 0.0;
    for(auto p : orderedProducts) {
        totalPrice += p->getPrice();
    }
    return totalPrice;
}

void Order::updateStatus(OrderStatus s) {
    status = s;
}

void Order::finaliseOrder() {
    if(!orderedProducts.empty()) {
        status = PROCESSING;
        // Builder is triggered here
        //go through ProductSpecs and make each product
    } else {
        std::cout << "Cannot finalise empty order.\n";
    }
}

// ================= Payment Status =================
bool Order::isPaid() {
    return paymentReveived;
}

void Order::togglePaymentStatus() {
    paymentReveived = !paymentReveived;
}

// ================= Order Details =================
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
int Order::getProductCount() {
    return orderedProducts.size();
}

Product* Order::getProduct() {
    if(!orderedProducts.empty()) {
        return orderedProducts.back(); // returns the last added product
    }
    return nullptr;
}
