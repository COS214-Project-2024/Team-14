/**
 * @file CapacityUpgrade.h
 * @brief Defines the CapacityUpgrade class for managing building capacity upgrades
 */
#pragma once
#include "BuildingUpgrade.h"

/**
 * @class CapacityUpgrade
 * @brief A class that handles capacity upgrades for buildings
 * @inherits BuildingUpgrade
 * 
 * CapacityUpgrade allows buildings to be upgraded to increase their capacity up to
 * a maximum level of 5. Each upgrade increases the cost of the building.
 */
class CapacityUpgrade : public BuildingUpgrade {
public:
    /**
     * @brief Constructs a CapacityUpgrade object
     * @param building Pointer to the Building object to be upgraded
     * 
     * Initializes the upgrade level based on the building's current capacity level
     */
    explicit CapacityUpgrade(Building* building)
        : BuildingUpgrade(building) {
        upgradeLevel = building->getCapacityLevel();
    }

    /**
     * @brief Gets the description of the upgraded building
     * @return String containing the building description with capacity upgrade information
     */
    std::string getDescription() const override {
        return building->getDescription() + " with Capacity Upgrade (Level " + std::to_string(upgradeLevel) + ")";
    }

    /**
     * @brief Calculates the cost of the next upgrade level
     * @return Double representing the cost of the next upgrade
     */
    double getUpgradeCost() const override {
        return 2000 * (upgradeLevel + 1);
    }

    /**
     * @brief Applies the capacity upgrade to the building
     * 
     * Increases the capacity level if below maximum (5), updates the building's cost,
     * and sets the new capacity level. Prints a message indicating success or maximum level reached.
     */
    void applyUpgrade() {
        if (upgradeLevel < 5) {
            double upgradeCost = getUpgradeCost();
            building->setCost(building->getCost() + upgradeCost);
            upgradeLevel++;
            building->setCapacityLevel(upgradeLevel);
            std::cout << "Capacity upgraded to level " << upgradeLevel << "\n";
        } else {
            std::cout << "Maximum capacity level reached (5)\n";
        }
    }
};