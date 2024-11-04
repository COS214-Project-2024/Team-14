#pragma once
#include "Building.h"

/**
 * @brief Decorator class that adds upgrade functionality to Building objects
 * 
 * The BuildingUpgrade class implements the decorator pattern to extend
 * Building objects with upgrade capabilities while preserving their core functionality.
 */
class BuildingUpgrade : public Building {
public:
    /**
     * @brief Constructs a BuildingUpgrade decorator around an existing Building
     * @param building Pointer to the Building object to be decorated
     */
    explicit BuildingUpgrade(Building* building)
        : Building(building->getName(), building->getFloorArea(), 
                  building->getMaxCapacity(), building->getCost()),
          building(building), upgradeLevel(0) {}
    
    /**
     * @brief Virtual destructor
     * @note Does not delete the wrapped building pointer as it's managed externally
     */
    virtual ~BuildingUpgrade() override {
        building = nullptr;
    }

    /**
     * @brief Gets the building's description
     * @return String containing the building's description
     */
    std::string getDescription() const override {
        return building->getDescription();
    }

    /**
     * @brief Gets the building's cost
     * @return Double representing the building's cost
     */
    double getCost() const override {
        return building->getCost();
    }

    /**
     * @brief Gets the building's type
     * @return String containing the building type identifier
     */
    std::string getBuildingType() const override {
        return building->getBuildingType();
    }

    /**
     * @brief Gets the building's floor area
     * @return Double representing the floor area in square meters
     */
    double getFloorArea() const override {
        return building->getFloorArea();
    }

    /**
     * @brief Gets the building's maximum capacity
     * @return Integer representing maximum number of occupants
     */
    int getMaxCapacity() const override {
        return building->getMaxCapacity();
    }

    void setMaxCapacity(int capacity) override {
        building->setMaxCapacity(capacity);
    }

    virtual double getUpgradeCost() const  {
    }

    void add(CityComponent* component) override {
        building->add(component);
    }

    void remove(CityComponent* component) override {
        building->remove(component);
    }

    int getUpgradeLevel() const {
        return upgradeLevel;
    }

    void incrementUpgradeLevel() {
        if (upgradeLevel < 5) {
            upgradeLevel++;
        } else {
            std::cout << "Upgrade level is already at maximum." << std::endl;
        }
    }

protected:
    Building* building;
    int upgradeLevel;
};