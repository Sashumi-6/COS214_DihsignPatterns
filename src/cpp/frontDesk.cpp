#include "frontDesk.h"

bool FrontDesk::placeOrder(std::vector<ProductRequest>& requests, std::string customerName){
    if(requests.empty()) return false;

    Cashier* cashier = getAvailableEmployee<Cashier>();
    currentOrder = new Order(cashier, customerName);
    for(const auto& reqs: requests){
        currentOrder->addRequest(reqs);
    }

    currentOrder->finaliseOrder(greenhouse); //requests get handled here
    return true;
}

template <typename T>
T* FrontDesk::getAvailableEmployee() {
    for (Employee* e : employees) {
        if (e->isAvailable()) {
            if (T* casted = dynamic_cast<T*>(e)) {
                return casted;
            }
        }
    }
    return nullptr;
}
