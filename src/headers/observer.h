#ifndef OBSERVER_H
#define OBSERVER_H

#include "plant.h"

class Observer {
    public:
        virtual void update() = 0;
};

class Customer : Observer {
    public:
        void update();
};

class Subject {
    public:
        void add(Plant* plant);
        void detach();
        void attach();

    private:
        Observer* clients;
};

class Specials {
    private:
        Plant* plants;
};

#endif