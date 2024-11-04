// IncomeTax.h
#pragma once
#include "TaxStrategy.h"

// Forward declaration
class CitizenPrototype;

/**
 * @class IncomeTax
 * @brief Class implementing income tax calculation strategy
 * 
 * This class provides functionality for calculating income tax
 * as a concrete implementation of the TaxStrategy interface.
 */
class IncomeTax : public TaxStrategy {
public:
    /**
     * @brief Default constructor
     */
    IncomeTax() = default;
    
    /**
     * @brief Virtual destructor
     */
    ~IncomeTax() override = default;
    
    /**
     * @brief Calculates tax for a given amount
     * @param amount The amount to calculate tax on
     * @return The calculated tax amount
     */
    double calculateTax(double amount) override;
    
    /**
     * @brief Calculates the total tax
     * @return The total tax amount
     */
    double calculateTotalTax();
}; 
