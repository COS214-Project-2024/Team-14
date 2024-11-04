//Building.h
#pragma once
#include "CityComponent.h"
#include "BaseBuilding.h"
#include <string>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include "BuildingState.h"
#include "Neighborhood.h"
#include <memory>
#include "ResourceConsumer.h"

// Forward declarations
class BuildingTax;

/**
 * @file Building.h
 * @brief Base class for all building types in the city simulation
 */

/**
 * @class Building
 * @brief Abstract base class representing a building in the city
 * @details Implements resource consumption, state management, and upgrades
 * 
 * @see CityComponent
 * @see BaseBuilding
 * @see ResourceConsumer
 */

class Building : public CityComponent, public BaseBuilding, public ResourceConsumer
{
private:
    BuildingTax *buildingTax;
    BuildingState *state;
    std::unordered_map<std::string, double> resourceRequirements;

protected:
    std::string buildingType;
    std::string name;
    double floorArea;
    int maxCapacity;
    int currentOccupancy = 0;
    bool maintenanceNeeded;
    double energyUsage;
    long double Cost;
    int securityLevel = 1;
    int capacityLevel = 1;
    int energyLevel = 1;

    Neighborhood *parentNeighborhood;
    std::unordered_map<std::string, int> resourceLevels;

public:
    inline static std::vector<Building *> buildings;
    virtual double calculateTax() const;
    virtual double calculateTotalTax() const;
    Building(const std::string &name, double area, int capacity, double cost); // Declaration only
    virtual ~Building();                                                       // Declaration only
    void setCost(long double cost);
    void print(int indent = 0) const override; // Declaration only

    void incrementOccupancy();

    void upgradeSecurity();
    void upgradeEnergyEfficiency();
    void upgradeCapacity();

    void setSecurityLevel(int level) { securityLevel = level; }
    void setEnergyLevel(int level) { energyLevel = level; }
    void setCapacityLevel(int level) { capacityLevel = level; }

    int getSecurityLevel() const { return securityLevel; }
    int getEnergyLevel() const { return energyLevel; }
    int getCapacityLevel() const { return capacityLevel; }

    void setState(BuildingState *newState);
    std::string getState() const;

    // Pure virtual functions
    virtual void setMaxCapacity(int capacity) = 0;
    virtual int getMaxCapacity() const = 0;
    virtual double getFloorArea() const = 0;
    virtual double getCost() const = 0;

    // Common functionality
    std::string getName() const override
    {
        return name;
    }
    void add(CityComponent *component) override
    {
        // Since Building is a leaf node in the Composite pattern,
        // it shouldn't support adding child components
        throw std::runtime_error("Cannot add components to a Building (Leaf node)");
    }

    void remove(CityComponent *component) override
    {
        // Since Building is a leaf node in the Composite pattern,
        // it shouldn't support removing child components
        throw std::runtime_error("Cannot remove components from a Building (Leaf node)");
    }

    void setParentNeighborhood(Neighborhood *neighborhood)
    {
        parentNeighborhood = neighborhood;
    }

    Neighborhood *getParentNeighborhood() const
    {
        return parentNeighborhood;
    }

    static void cleanup() {
        buildings.clear(); // Clear the vector but don't delete the objects
    }

    double getResourceRequirement(const std::string& resourceType) const {

        auto it = resourceRequirements.find(resourceType);

        if (it != resourceRequirements.end()) {

            return it->second;

        }

        return 0.0;

    }

    // ResourceConsumer implementation
    void receiveResource(const std::string& resource, int amount) override {
        resourceLevels[resource] += amount;
    }
    
    int getResourceLevel(const std::string& resource) const override {
        auto it = resourceLevels.find(resource);
        return (it != resourceLevels.end()) ? it->second : 0;
    }
    
    bool needsResource(const std::string& resource) const override {
        auto req = resourceRequirements.find(resource);
        auto level = resourceLevels.find(resource);
        
        // Need resource if we have a requirement and current level is less than required
        if (req != resourceRequirements.end()) {
            int currentLevel = (level != resourceLevels.end()) ? level->second : 0;
            return currentLevel < req->second;
        }
        return false;
    }

    void setResourceRequirement(const std::string& resource, int amount) {
        resourceRequirements[resource] = amount;
    }
};

#include "BuildingTax.h"
#include "IncomeTax.h"