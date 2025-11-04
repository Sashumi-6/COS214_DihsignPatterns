/**
 * @file garden.h
 * @brief Declares the composite structure representing greenhouse sections.
 *
 * Defines the base @ref GardenComponent interface as well as the composite
 * section node used to hold other components or plants.
 */
#ifndef GARDEN_H
#define GARDEN_H

#include <vector>

template <typename T> class Iterator;
class PlantOnlyIterator;

/**
 * @brief Abstract component in the greenhouse composite structure.
 */
class GardenComponent {
  public:
    /**
     * @brief Applies water to the component.
     */
    virtual void waterPlant() = 0;
    /**
     * @brief Exposes the component to sunlight.
     */
    virtual void exposeToSunlight() = 0;
    /**
     * @brief Causes the component to lose water.
     */
    virtual void loseWater() = 0;
    GardenComponent() = default;
    GardenComponent(const GardenComponent&) = default;
    GardenComponent& operator=(const GardenComponent&) = default;
    GardenComponent(GardenComponent&&) noexcept = default;
    GardenComponent& operator=(GardenComponent&&) noexcept = default;
    virtual ~GardenComponent() = default;
    /**
     * @brief Indicates if the component is ready for sale.
     */
    virtual bool canSell() = 0;
    /**
     * @brief Triggers growth operations on the component.
     */
    virtual void grow() = 0;
    /**
     * @brief Adds a child component to the composite.
     */
    virtual void add(GardenComponent* param) = 0;
    /**
     * @brief Retrieves a specific child by index.
     */
    virtual GardenComponent* getChild(int param) = 0;
    /**
     * @brief Returns any children for iteration.
     */
    virtual std::vector<GardenComponent*> getChildren() const { return {}; }
    /**
     * @brief Removes a child component.
     */
    virtual void remove(GardenComponent* param) = 0;
    /**
     * @brief Creates an iterator for traversing children.
     */
    virtual Iterator<GardenComponent>* createIterator() = 0;
    /**
     * @brief Identifies whether the component is a leaf node.
     */
    virtual bool isLeaf() const = 0;
};

/**
 * @brief Composite node representing a section in the greenhouse.
 */
class GardenSection : public GardenComponent { ///TODO THIS IS JUST HERE FOR TESTING PLEASE CHANGE!!!!!!!!!!! 
  public:
    /**
     * @brief Waters all child components.
     */
    void waterPlant() override;
    /**
     * @brief Exposes all child components to sunlight.
     */
    void exposeToSunlight() override;
    /**
     * @brief Causes water loss across children.
     */
    void loseWater() override;
    /**
     * @brief Evaluates if any child can be sold.
     */
    bool canSell() override;
    /**
     * @brief Triggers growth on every child.
     */
    void grow() override;
    /**
     * @brief Adds a child component to the section.
     */
    void add(GardenComponent* param) override;
    /**
     * @brief Retrieves a child by index.
     */
    GardenComponent* getChild(int param) override;
    /**
     * @brief Provides access to all child components.
     */
    std::vector<GardenComponent*> getChildren() const override;
    /**
     * @brief Removes a child component from the section.
     */
    void remove(GardenComponent* param) override;
    /**
     * @brief Creates an iterator traversing the section tree.
     */
    Iterator<GardenComponent>* createIterator() override;
    /**
     * @brief Returns false because sections are composite nodes.
     */
    bool isLeaf() const override;

  private:
    /** Child components contained within the section. */
    std::vector<GardenComponent*> children;
};

#endif
