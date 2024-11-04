/**
 * @file BaseBuilding.h
 * @brief Base interface for all building types
 */

#pragma once
#include <string>

/**
 * @class BaseBuilding
 * @brief Abstract base class defining core building interface
 * @details Provides pure virtual functions for basic building operations
 */

class BaseBuilding {
public:
    /**
     * @brief Get building description
     * @return std::string Description of the building
     */
    virtual std::string getDescription() const = 0;

    /**
     * @brief Get building cost
     * @return double Cost of the building
     */
    virtual double getCost() const = 0;

    /**
     * @brief Virtual destructor
     */
    virtual ~BaseBuilding() = default;
};