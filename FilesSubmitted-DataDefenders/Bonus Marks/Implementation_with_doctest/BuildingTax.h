/**
 * @file BuildingTax.h
 * @brief Tax calculation strategy for buildings
 */

#pragma once
#include "TaxStrategy.h"

class Building; // Forward declaration

/**
 * @class BuildingTax
 * @brief Concrete strategy for calculating building taxes
 * @details Implements TaxStrategy for building-specific tax calculations
 * 
 * @see TaxStrategy
 * @see Building
 */
class BuildingTax : public TaxStrategy {
public:
    BuildingTax() = default;
    ~BuildingTax() override = default;
    
    /**
     * @brief Calculate tax for a building
     * @param amount Base amount for tax calculation
     * @return double Calculated tax amount
     */
    double calculateTax(double amount) override;

    /**
     * @brief Calculate total tax for all buildings
     * @return double Total tax amount
     */
    double calculateTotalTax();
};