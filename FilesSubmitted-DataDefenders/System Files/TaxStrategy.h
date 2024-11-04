/**
 * @file TaxStrategy.h
 * @brief Defines the interface for different tax calculation strategies
 */

#pragma once

/**
 * @class TaxStrategy
 * @brief Abstract base class for implementing various tax calculation strategies
 */
class TaxStrategy
{
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~TaxStrategy() = default;

    /**
     * @brief Pure virtual function for calculating tax
     * @param amount The base amount to calculate tax on
     * @return double The calculated tax amount
     */
    virtual double calculateTax(double amount) = 0;
};