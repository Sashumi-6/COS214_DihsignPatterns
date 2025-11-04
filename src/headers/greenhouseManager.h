#ifndef GREENHOUSEMANAGER_H
#define GREENHOUSEMANAGER_H

#include <string>
#include <unordered_map>

class GardenSection;
class Plant;

class GreenHouseManager {
  public:
    GreenHouseManager(GardenSection* root, std::string rootName = "root");

    GardenSection* getRoot() const;
    GardenSection* addSection(const std::string& sectionName);
    GardenSection* addSection(const std::string& sectionName, const std::string& parentSection);
    void addPlant(Plant* plant);
    Plant* find(const std::string& name) const;
    Plant* findMature(const std::string& name) const;
    bool removePlant(Plant* plant);
    bool removePlant(const std::string& name);
    void clearAllDead();

  private:
    GardenSection* findSection(const std::string& sectionName) const;
    GardenSection* ensureSection(const std::string& sectionName);
    std::string resolveSectionForPlant(const Plant* plant) const;
    void indexSection(const std::string& sectionName, GardenSection* section);
    bool removePlantFromSection(GardenSection* section, Plant* plant);

    GardenSection* root;
    std::unordered_map<std::string, GardenSection*> sectionIndex;
    std::string rootName;
};

#endif
