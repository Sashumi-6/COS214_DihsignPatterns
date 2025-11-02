#include "../headers/iterator.h"

GardenIterator::GardenIterator(GardenComponent* root) : root(root) { first(); }

GardenComponent* GardenIterator::first() {
    while (!stack.empty()) {
        stack.pop();
    }
    if (root != nullptr) {
        stack.push(root);
    }
    return next();
}

GardenComponent* GardenIterator::next() {
    while (!stack.empty()) {
        GardenComponent* curr = stack.top();
        stack.pop();
        if (curr->isLeaf()) {
            return curr;
        }

        std::vector<GardenComponent*> children = curr->getChildren();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            stack.push(*it);
        }
    }
    return nullptr;
}

bool GardenIterator::isDone() const { return stack.empty(); }