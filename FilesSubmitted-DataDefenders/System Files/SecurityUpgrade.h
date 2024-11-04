/**
 * @file SecurityUpgrade.h
 * @brief Defines the SecurityUpgrade decorator class for building security enhancements
 */

#pragma once
#include "BuildingUpgrade.h"

/**
 * @class SecurityUpgrade
 * @brief A decorator class that adds security upgrades to buildings
 * @inherits BuildingUpgrade
 */
class SecurityUpgrade : public BuildingUpgrade {
public:
    /**
     * @brief Constructor that initializes the security upgrade
     * @param building Pointer to the building to be upgraded
     */
    explicit SecurityUpgrade(Building* building)
        : BuildingUpgrade(building) {
        // Initialize upgradeLevel from building's current security level
        upgradeLevel = building->getSecurityLevel();
    }

    /**
     * @brief Gets the description of the building with security upgrade
     * @return std::string Description including the security level
     */
    std::string getDescription() const override {
        return building->getDescription() + " with Security Upgrade (Level " + std::to_string(upgradeLevel) + ")";
    }

    /**
     * @brief Calculates the cost of the next security upgrade
     * @return double Cost of the upgrade in currency units
     */
    double getUpgradeCost() const override {
        return 5000 * (upgradeLevel + 1); // Cost for next level
    }

    /**
     * @brief Applies the security upgrade to the building
     * 
     * Increases the security level and updates the building's cost if the maximum
     * level (5) hasn't been reached.
     */
    void applyUpgrade() {
        if (upgradeLevel < 5) {  // Check current level
            double upgradeCost = getUpgradeCost();
            building->setCost(building->getCost() + upgradeCost);
            upgradeLevel++;  // Increment first
            building->setSecurityLevel(upgradeLevel);  // Then set new level
            std::cout << "Security upgraded to level " << upgradeLevel << "\n";
        } else {
            std::cout << "Maximum security level reached (5)\n";
        }
    }
};