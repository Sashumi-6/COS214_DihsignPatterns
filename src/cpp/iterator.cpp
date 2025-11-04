/**
 * @file iterator.cpp
 * @brief Implements greenhouse iterators for plants and sections.
 */
#include "../headers/iterator.h"

/**
 * @brief Sets up the plant-only iterator and positions it at the first element.
 */
PlantOnlyIterator::PlantOnlyIterator(GardenComponent* root) : root(root) { first(); }

/**
 * @brief Resets the iterator to the first plant leaf.
 */
GardenComponent* PlantOnlyIterator::first() {
    while (!stack.empty()) {
        stack.pop();
    }
    if (root != nullptr) {
        stack.push(root);
    }
    return next();
}

/**
 * @brief Advances to the next available plant leaf in depth-first order.
 */
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

/**
 * @brief Indicates whether all plant leaves have been visited.
 */
bool PlantOnlyIterator::isDone() const { return stack.empty(); }

/**
 * @brief Sets up the section-only iterator and positions it at the first section.
 */
SectionOnlyIterator::SectionOnlyIterator(GardenComponent* root) : root(root) { first(); }

/**
 * @brief Resets the iterator to the first section node.
 */
GardenComponent* SectionOnlyIterator::first() {
    while (!stack.empty()) {
        stack.pop();
    }
    if (root != nullptr) {
        stack.push(root);
    }
    return next();
}

/**
 * @brief Advances to the next section in the traversal.
 */
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

/**
 * @brief Indicates whether all sections have been visited.
 */
bool SectionOnlyIterator::isDone() const { return stack.empty(); }

/**
 * @brief Sets up the full iterator and positions it at the first component.
 */
FullIterator::FullIterator(GardenComponent* root) : root(root) { first(); }

/**
 * @brief Resets the iterator to the root component.
 */
GardenComponent* FullIterator::first() {
    while (!queue.empty()) {
        queue.pop();
    }
    if (root != nullptr) {
        queue.push(root);
    }
    return next();
}

/**
 * @brief Advances to the next component in breadth-first order.
 */
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

/**
 * @brief Indicates whether all components have been visited.
 */
bool FullIterator::isDone() const { return queue.empty(); }
