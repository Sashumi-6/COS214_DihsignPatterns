#include "../headers/iterator.h"

PlantOnlyIterator::PlantOnlyIterator(GardenComponent* root) : root(root) { first(); }

GardenComponent* PlantOnlyIterator::first() {
    while (!stack.empty()) {
        stack.pop();
    }
    if (root != nullptr) {
        stack.push(root);
    }
    return next();
}

GardenComponent* PlantOnlyIterator::next() {
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

bool PlantOnlyIterator::isDone() const { return stack.empty(); }

SectionOnlyIterator::SectionOnlyIterator(GardenComponent* root) : root(root) {
    first();
}

GardenComponent* SectionOnlyIterator::first() {
    while (!stack.empty()) {
        stack.pop();
    }
    if (root != nullptr) {
        stack.push(root);
    }
    return next();
}

GardenComponent* SectionOnlyIterator::next() {
    while (!stack.empty()) {
        GardenComponent* curr = stack.top();
        stack.pop();

        std::vector<GardenComponent*> children = curr->getChildren();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            stack.push(*it);
        }

        if (!curr->isLeaf()) {
            return curr;
        }
    }
    return nullptr;
}

bool SectionOnlyIterator::isDone() const { return stack.empty(); }

FullIterator::FullIterator(GardenComponent* root) : root(root) { first(); }

GardenComponent* FullIterator::first() {
    while (!queue.empty()) {
        queue.pop();
    }
    if (root != nullptr) {
        queue.push(root);
    }
    return next();
}

GardenComponent* FullIterator::next() {
    while (!queue.empty()) {
        GardenComponent* curr = queue.front();
        queue.pop();
        std::vector<GardenComponent*> children = curr->getChildren();
        for (auto* child : children) {
            if (child != nullptr) {
                queue.push(child);
            }
        }
        return curr;
    }
    return nullptr;
}

bool FullIterator::isDone() const { return queue.empty(); }
