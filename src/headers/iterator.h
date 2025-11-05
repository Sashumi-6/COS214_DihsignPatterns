/**
 * @file iterator.h
 * @brief Declares iterators for traversing greenhouse components.
 *
 * Provides generic iterator interface and specialized implementations for
 * plants, sections, and full breadth-first traversal.
 */
#ifndef ITERATOR_H
#define ITERATOR_H

#include <queue>
#include <stack>

#include "../headers/garden.h"

/**
 * @brief Generic iterator interface for greenhouse components.
 * @tparam T Component type returned by the iterator.
 */
template <typename T> class Iterator {
  public:
    /**
     * @brief Positions the iterator at the first element.
     * @return Pointer to first element or nullptr when empty.
     */
    virtual T* first() = 0;
    /**
     * @brief Advances the iterator.
     * @return Pointer to next element or nullptr.
     */
    virtual T* next() = 0;
    /**
     * @brief Indicates whether the iterator has no more elements.
     */
    virtual bool isDone() const = 0;
    virtual ~Iterator() = default;
    // virtual T* currentItem() = 0;
};

/**
 * @brief Depth-first iterator that yields only plant leaf nodes.
 */
class PlantOnlyIterator : public Iterator<GardenComponent> {
  public:
    /**
     * @brief Constructs the iterator rooted at the provided component.
     * @param root Root component to start traversal from.
     */
    explicit PlantOnlyIterator(GardenComponent* root);
    GardenComponent* first() override;
    GardenComponent* next() override;
    bool isDone() const override;

  private:
    /** Stack used for depth-first traversal. */
    std::stack<GardenComponent*> stack;
    /** Root component for iteration. */
    GardenComponent* root;
};

/**
 * @brief Depth-first iterator that returns only section composite nodes.
 */
class SectionOnlyIterator : public Iterator<GardenComponent> {
  public:
    /**
     * @brief Constructs the iterator rooted at the provided component.
     * @param root Root component to start traversal from.
     */
    explicit SectionOnlyIterator(GardenComponent* root);
    GardenComponent* first() override;
    GardenComponent* next() override;
    bool isDone() const override;

  private:
    /** Stack storing sections during traversal. */
    std::stack<GardenComponent*> stack;
    /** Root component for iteration. */
    GardenComponent* root;
};

/**
 * @brief Breadth-first iterator that visits every greenhouse component.
 */
class FullIterator : public Iterator<GardenComponent> {
  public:
    /**
     * @brief Constructs the iterator rooted at the provided component.
     * @param root Root component to start traversal from.
     */
    explicit FullIterator(GardenComponent* root);
    GardenComponent* first() override;
    GardenComponent* next() override;
    bool isDone() const override;

  private:
    /** Queue providing breadth-first traversal order. */
    std::queue<GardenComponent*> queue;
    /** Root component for iteration. */
    GardenComponent* root;
};

#endif
