/**
 * @file EnergyEfficiencyUpgrade.h
 * @brief Implements energy efficiency upgrades for buildings
 */

/**
 * @class EnergyEfficiencyUpgrade
 * @brief Handles energy efficiency upgrades for buildings
 * @details Implements the upgrade system for building energy efficiency with 5 levels
 */
class EnergyEfficiencyUpgrade : public BuildingUpgrade {
public:
    /**
     * @brief Constructor
     * @param building Pointer to the building to be upgraded
     */
    explicit EnergyEfficiencyUpgrade(Building* building)
        : BuildingUpgrade(building) {
        // Set initial upgradeLevel based on building's current level
        upgradeLevel = building->getEnergyLevel();
    }

    /**
     * @brief Applies an energy efficiency upgrade to the building
     * @details Increases energy efficiency level if not at maximum (level 5)
     */
    void applyUpgrade() {
        if (upgradeLevel < 5) {  // Check current level
            double upgradeCost = getUpgradeCost();
            building->setCost(building->getCost() + upgradeCost);
            upgradeLevel++;  // Increment first
            building->setEnergyLevel(upgradeLevel);  // Then set new level
            std::cout << "Energy efficiency upgraded to level " << upgradeLevel << "\n";
        } else {
            std::cout << "Maximum energy efficiency level reached (5)\n";
        }
    }

    /**
     * @brief Calculates the cost of the next upgrade
     * @return Cost of the next upgrade level
     */
    double getUpgradeCost() const override {
        return 3000 * (upgradeLevel + 1); // Cost for next level
    }
};