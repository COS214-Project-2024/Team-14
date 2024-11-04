/**
 * @file TaxSystem.h
 * @brief Defines the tax system class that uses different tax calculation strategies
 */

#pragma once
#include "TaxStrategy.h"

/**
 * @class TaxSystem
 * @brief Implements the Strategy pattern for tax calculations
 * 
 * This class manages different tax calculation strategies and delegates
 * the actual tax computation to the current strategy.
 */
class TaxSystem {
private:
    TaxStrategy* strategy; /**< Current tax calculation strategy */

public:
    /**
     * @brief Constructor that initializes the tax system with a strategy
     * @param strategy Pointer to the initial tax calculation strategy
     */
    TaxSystem(TaxStrategy* strategy) : strategy(strategy) {}
    
    /**
     * @brief Destructor that ensures proper cleanup of the strategy
     */
    ~TaxSystem() {
        delete strategy;
    }
    
    /**
     * @brief Changes the current tax calculation strategy
     * @param newStrategy Pointer to the new tax calculation strategy
     */
    void setStrategy(TaxStrategy* newStrategy) {
        delete strategy;
        strategy = newStrategy;
    }
    
    /**
     * @brief Calculates tax using the current strategy
     * @param amount The base amount to calculate tax on
     * @return double The calculated tax amount
     */
    double calculateTax(double amount) {
        return strategy->calculateTax(amount);
    }
};