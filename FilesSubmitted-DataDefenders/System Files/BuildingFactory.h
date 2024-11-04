/**
 * @file BuildingFactory.h
 * @brief Abstract factory class for creating Building objects
 */

#pragma once
#include "Building.h"
#include <string>
#include <stdexcept>

/**
 * @class BuildingFactory
 * @brief Abstract factory class that defines interface for creating Building objects
 */
class BuildingFactory
{
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~BuildingFactory() = default;

    /**
     * @brief Pure virtual function to create Building objects
     * @param type Type of the building to create
     * @param name Name of the building
     * @param area Area of the building in square meters
     * @param capacity Maximum capacity of the building
     * @param cost Cost of the building
     * @param districtName Name of the district (defaults to "Default District")
     * @param neighborhoodName Name of the neighborhood (defaults to "Default Neighborhood")
     * @return Pointer to newly created Building object
     * @throws std::invalid_argument if invalid parameters are provided
     */
    virtual Building* createBuilding(
        const std::string& type,
        const std::string& name,
        double area,
        int capacity,
        double cost,
        const std::string& districtName = "Default District",
        const std::string& neighborhoodName = "Default Neighborhood"
    ) const = 0;
};