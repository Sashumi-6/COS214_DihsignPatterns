/**
 * @file plant.h
 * @brief Declares plant components, strategies, and state machine for garden simulation.
 *
 * Provides the Plant composite leaf implementation, associated strategy interfaces for
 * sunlight and water loss, and the state pattern used to manage plant lifecycle changes.
 */
#ifndef PLANT_H
#define PLANT_H

#include "garden.h"
#include <string>
#include "command.h"
#include <string>

class PlantState;

/**
 * @brief Enumerates the possible locations where a plant may reside.
 */
enum class PlantLocation { OUTSIDE, GREENHOUSE, INSIDE };

/**
 * @brief Strategy interface controlling how plants lose water over time.
 */
class WaterLossStrategy {
  public:
    virtual ~WaterLossStrategy() = default;
    /**
     * @brief Calculates the amount of water lost for the current time step.
     * @return Water loss as a ratio of total water volume.
     */
    virtual double loseWater() = 0;
};

/**
 * @brief Water loss strategy representing resilient plants requiring little water.
 */
class LowWaterLoss : public WaterLossStrategy {
  public:
    /**
     * @copydoc WaterLossStrategy::loseWater()
     */
    double loseWater() override;

  private:
    static constexpr double kLossAmount = 0.1;
};

/**
 * @brief Water loss strategy representing plants with moderate water needs.
 */
class MedWaterLoss : public WaterLossStrategy {
  public:
    /**
     * @copydoc WaterLossStrategy::loseWater()
     */
    double loseWater() override;

  private:
    static constexpr double kLossAmount = 0.25;
};

/**
 * @brief Water loss strategy representing very thirsty plants.
 */
class HighWaterLoss : public WaterLossStrategy {
  public:
    /**
     * @copydoc WaterLossStrategy::loseWater()
     */
    double loseWater() override;

  private:
    static constexpr double kLossAmount = 0.35;
};

/**
 * @brief Strategy interface determining how plants are exposed to sunlight.
 */
class SunlightStrategy {
  public:
    virtual ~SunlightStrategy() = default;
    /**
     * @brief Decides where the plant should be placed for sunlight.
     * @return Target @ref PlantLocation for current sunlight strategy.
     */
    virtual PlantLocation exposeToSun() = 0;
};

/**
 * @brief Sunlight strategy assigning plants to low-light areas.
 */
class LowSunlightStrategy : public SunlightStrategy {
  public:
    /**
     * @copydoc SunlightStrategy::exposeToSun()
     */
    PlantLocation exposeToSun() override;
};

/**
 * @brief Sunlight strategy assigning plants to medium-light areas.
 */
class MedSunlightStrategy : public SunlightStrategy {
  public:
    /**
     * @copydoc SunlightStrategy::exposeToSun()
     */
    PlantLocation exposeToSun() override;
};

/**
 * @brief Sunlight strategy assigning plants to high-light environments.
 */
class HighSunlightStrategy : public SunlightStrategy {
  public:
    /**
     * @copydoc SunlightStrategy::exposeToSun()
     */
    PlantLocation exposeToSun() override;
};

/**
 * @brief Leaf node in the garden composite representing an individual plant.
 */
class Plant : public GardenComponent {
  public:
        /**
         * @brief Default starting water level for new plants.
         */
        static constexpr double kInitialWaterLevel = 1.0;
        /**
         * @brief Standard amount of water to apply when watering a plant.
         */
        static constexpr double kWaterDose = 0.35;
        /**
         * @brief Constructs a plant with its strategies and initial state.
         * @param name Plant display name.
         * @param price Monetary value when sold.
         * @param waterLossStrategy Strategy controlling dehydration.
         * @param sunlightStrategy Strategy deciding sunlight exposure.
         * @param state Initial lifecycle state.
         */
        Plant(std::string name , double price , WaterLossStrategy* waterLossStrategy , SunlightStrategy* sunlightStrategy , PlantState* state) ;
        /**
         * @brief Copy constructor for duplicating plants.
         * @param other Plant to copy from.
         */
        Plant(const Plant& other) = default;//TODO add to UML. changeeeeeee
        /**
         * @brief Destroys the plant and associated strategy/state objects.
         */
        virtual ~Plant() override; // TODO change
        /**
         * @brief Water the plant using @ref kWaterDose and delegate to strategy.
         */
        void waterPlant() override;
        /**
         * @brief Expose the plant to sunlight based on its sunlight strategy.
         */
        void exposeToSunlight() override;
        /**
         * @brief Applies the configured water loss strategy.
         */
        void loseWater() override;
        /**
         * @brief Determines if the plant meets the criteria for sale.
         * @return True when the current state authorizes selling.
         */
        bool canSell() override;
        /**
         * @brief Attempts to grow the plant, advancing its state when possible.
         */
        void grow() override;
        /**
         * @brief Disallows adding child components since plants are leaves.
         * @throws std::logic_error When called.
         */
        void add(GardenComponent* param) override;
        /**
         * @brief Always returns null because plants do not have children.
         */
        GardenComponent* getChild(int param) override;
        /**
         * @brief Disallows child removal because plants are leaves.
         * @throws std::logic_error When called.
         */
        void remove(GardenComponent* param) override;
        /**
         * @brief Provides an iterator over the plant (leaf iterator).
         */
        Iterator<GardenComponent>* createIterator() override;
        /**
         * @brief Helper that applies configured water loss and updates state.
         */
        void applyWaterLoss();
        /**
         * @brief Helper exposing the plant to sunlight via strategy decision.
         */
        void applyExposeToSunlight();
        /**
         * @brief Changes the internal state object and updates its back-reference.
         * @param newState State instance to install.
         */
        void setState(PlantState* newState);
        /**
         * @brief Adds raw water to the plant's water level.
         * @param amount Water amount between 0 and 1.
         */
        void addWater(double amount);
        /**
         * @brief Reports the plant's preferred sunlight amount.
         * @return Preferred sunlight descriptor.
         */
         SunlightPreference getSunlightPreference() const;
        /**
         * @brief Reports the plant's preferred watering frequency.
         * @return Preferred watering descriptor.
         */
         WaterPreference getWaterPreference() const;
        /**
         * @brief Accessor for plant price.
         */
        double getPrice();
        /**
         * @brief Accessor for plant name.
         */
        const std::string& getName() const;
        /**
         * @brief Indicates if the plant has reached maturity.
         */
        bool isMature() const;
        /**
         * @brief Indicates if the plant is considered dead.
         */
        bool isDead() const;
        /**
         * @brief Always true for leaf nodes.
         */
        bool isLeaf() const override;
        /**
         * @brief Attempts to advance growth based on current resources.
         */
        void tryGrow();

    private:
        /** Strategy controlling water dehydration. */
        WaterLossStrategy* waterLossStrategy;
        /** Strategy controlling sunlight exposure. */
        SunlightStrategy* sunlightStrategy;
        /** Current physical location derived from sunlight strategy. */
        PlantLocation location;
        /** Display name for the plant. */
        std::string name;
        /** State machine tracking lifecycle progression. */
        PlantState* state;
        /** Sale price for the plant. */
        double price;
        /** Current water level between 0 (dry) and 1 (full). */
        double waterLevel;
        /** Number of growth cycles completed. */
        int age;
        
};

/**
 * @brief Abstract base state used by the plant state machine.
 */
class PlantState {
  public:
    virtual ~PlantState() = default;
    /**
     * @brief Default constructor for subclasses.
     */
    PlantState() ;
    /**
     * @brief Disabled assignment that keeps state objects unique.
     */
    PlantState* operator=(const PlantState& other);//TODO add to UML
    /**
     * @brief Initializes the state with an owning plant.
     * @param plant Plant containing this state.
     */
    explicit PlantState(Plant* plant) ;
    /**
     * @brief Updates the plant the state manipulates.
     * @param newPlant Owning plant pointer.
     */
    void setPlant(Plant* newPlant) ; 
    /**
     * @brief Handles watering transition logic for the current state.
     */
    virtual void handleWaterPlant() = 0;
    /**
     * @brief Handles sunlight exposure transition logic for the current state.
     */
    virtual void handleExposeToSunlight() = 0;
    /**
     * @brief Verifies whether the plant can be sold in this state.
     * @return True if selling is permitted.
     */
    virtual bool canSell() = 0;
    /**
     * @brief Executes growth logic for the state.
     */
    virtual void handleGrow() = 0;
    /**
     * @brief Processes water loss behavior for the state.
     */
    virtual void handleLoseWater() = 0;

  protected:
    /** Plant that owns this state instance. */
    Plant* plant;
};

/**
 * @brief Represents a newly planted seedling that cannot be sold yet.
 */
class SeedlingState : public PlantState {
  public:
    /**
     * @brief Constructs the seedling state.
     * @param plant Plant owning the state.
     */
    explicit SeedlingState(Plant* plant);
    /**
     * @copydoc PlantState::handleWaterPlant()
     */
    void handleWaterPlant() override;
    /**
     * @copydoc PlantState::handleExposeToSunlight()
     */
    void handleExposeToSunlight() override;
    /**
     * @copydoc PlantState::canSell()
     */
    bool canSell() override;
    /**
     * @copydoc PlantState::handleGrow()
     */
    void handleGrow() override;
    /**
     * @copydoc PlantState::handleLoseWater()
     */
    void handleLoseWater() override;
};

/**
 * @brief Represents a fully grown plant ready for sale.
 */
class MatureState : public PlantState {
  public:
    /**
     * @brief Constructs the mature state.
     * @param plant Plant owning the state.
     */
    explicit MatureState(Plant* plant);
    /**
     * @copydoc PlantState::handleWaterPlant()
     */
    void handleWaterPlant() override;
    /**
     * @copydoc PlantState::handleExposeToSunlight()
     */
    void handleExposeToSunlight() override;
    /**
     * @copydoc PlantState::canSell()
     */
    bool canSell() override;
    /**
     * @copydoc PlantState::handleGrow()
     */
    void handleGrow() override;
    /**
     * @copydoc PlantState::handleLoseWater()
     */
    void handleLoseWater() override;
};

/**
 * @brief Represents plants that have depleted resources and are dead.
 */
class DeadState : public PlantState {
  public:
    /**
     * @brief Constructs the dead state.
     * @param plant Plant owning the state.
     */
    explicit DeadState(Plant* plant);
    /**
     * @copydoc PlantState::handleWaterPlant()
     */
    void handleWaterPlant() override;
    /**
     * @copydoc PlantState::handleExposeToSunlight()
     */
    void handleExposeToSunlight() override;
    /**
     * @copydoc PlantState::canSell()
     */
    bool canSell() override;
    /**
     * @copydoc PlantState::handleGrow()
     */
    void handleGrow() override;
    /**
     * @copydoc PlantState::handleLoseWater()
     */
    void handleLoseWater() override;
};

#endif
