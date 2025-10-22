#ifndef DECORATOR_H
#define DECORATOR_H

#include <string>
class Plant;

class Product {
    private:
        Plant* plant;
        std::string soil, container, card, wrapping;
};

class Bouquet : public Product {

};

class BasicProduct : public Product {

};

class Decorator : public Product {
    private:
        Product* component;
};

class WrappingPaper : public Decorator {

};

class Card : public Decorator {

};

#endif