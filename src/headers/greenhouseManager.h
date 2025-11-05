/**
 * @file greenhouseManager.h
 * @brief Declares the manager responsible for greenhouse section organization.
 *
 * The @ref GreenHouseManager provides section indexing, plant lookup, and
 * maintenance utilities for the composite greenhouse structure.
 */
#ifndef GREENHOUSEMANAGER_H
#define GREENHOUSEMANAGER_H

#include <string>
#include <unordered_map>

class GardenSection;
class Plant;

/**
 * @brief Maintains indexing and operations for greenhouse sections and plants.
 */
class GreenHouseManager {
  public:
    /**
     * @brief Constructs the manager for an existing greenhouse root.
     * @param root Root section node.
     * @param rootName Friendly name for the root section.
     */
    GreenHouseManager(GardenSection* root, std::string rootName = "root");

    /**
     * @brief Returns the root section node.
     */
    GardenSection* getRoot() const;
    /**
     * @brief Adds a new section beneath the root.
     * @param sectionName Name of the new section.
     * @return Pointer to new section.
     */
    GardenSection* addSection(const std::string& sectionName);
    /**
     * @brief Adds a new section beneath a specified parent.
     * @param sectionName Name of new section.
     * @param parentSection Name of parent section.
     * @return Pointer to new section.
     */
    GardenSection* addSection(const std::string& sectionName, const std::string& parentSection);
    /**
     * @brief Inserts a plant into an appropriate section.
     * @param plant Plant to add.
     */
    void addPlant(Plant* plant);
    /**
     * @brief Finds a plant by name across all sections.
     * @param name Plant name.
     * @return Pointer when found, nullptr otherwise.
     */
    Plant* find(const std::string& name) const;
    /**
     * @brief Finds a mature plant by name.
     * @param name Plant name.
     * @return Pointer when a mature plant is found.
     */
    Plant* findMature(const std::string& name) const;
    /**
     * @brief Removes a plant from its section.
     * @param plant Plant pointer to remove.
     * @return True when removal succeeded.
     */
    bool removePlant(Plant* plant);
    /**
     * @brief Removes a plant by name.
     * @param name Plant name.
     * @return True on success.
     */
    bool removePlant(const std::string& name);
    /**
     * @brief Removes all dead plants from the greenhouse.
     */
    void clearAllDead();

  private:
    /**
     * @brief Retrieves a section by name.
     */
    GardenSection* findSection(const std::string& sectionName) const;
    /**
     * @brief Ensures a section exists, creating it if absent.
     */
   GardenSection* ensureSection(const std::string& sectionName);
    /**
     * @brief Determines the appropriate section name for a plant.
     */
    std::string resolveSectionForPlant(const Plant* plant) const;
    /**
     * @brief Adds a section to the index for quick lookup.
     */
    void indexSection(const std::string& sectionName, GardenSection* section);
    /**
     * @brief Removes a plant from a target section.
     */
    bool removePlantFromSection(GardenSection* section, Plant* plant);

    /** Root section pointer for greenhouse structure. */
    GardenSection* root;
    /** Lookup map from section names to section nodes. */
    std::unordered_map<std::string, GardenSection*> sectionIndex;
    /** Friendly name for the root section. */
    std::string rootName;
};

#endif
