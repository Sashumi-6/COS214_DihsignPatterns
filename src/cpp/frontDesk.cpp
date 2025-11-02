#include "frontDesk.h"

bool FrontDesk::placeOrder(std::vector<ProductRequest>& requests, std::string customerName){
    if(requests.empty()) return false;

    Order* order = new Order(activeCashier, customerName);
    for(const auto& reqs: requests){
        order->addRequest(reqs);
    }

    order->finaliseOrder(greenhouse); //requests get handled here
    return true;
}