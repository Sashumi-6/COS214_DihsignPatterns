#include "employee.h"

//-------EMPLOYEE CLASS----------
void Employee::setNext(Employee* next){
    nextHandler = next;
}
        
bool Employee::isAvailable(){
    if(state == AVAILABLE) return true;

    return false;
}

//--------CASHIER CLASS----------
//For request commands
void Cashier::handleRequest(){

}
//Checks if they can handle the request command
bool Cashier::canHandle(Command* c){

}
Product* Cashier::constructBasic(){

}
Product* Cashier::constructBouquet(){

}
void Cashier::addItem(std::string type, std::string name){

}
void Cashier::removeItem(std::string type, std::string name){

}

void Cashier::fufill(){

}