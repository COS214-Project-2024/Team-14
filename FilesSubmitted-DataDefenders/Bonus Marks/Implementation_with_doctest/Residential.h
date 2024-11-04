/**
 * @file Residential.h
 * @brief Defines the Residential class for managing residential buildings
 * @inherit Building
 */
#pragma once
#include "Building.h"
#include <iostream>

/**
 * @class Residential
 * @brief Represents a residential building in the city system
 * 
 * This class manages residential buildings, including their properties
 * such as name, area, capacity, and cost.
 */
class Residential : public Building
{
public:
    /**
     * @brief Constructor for creating a residential building
     * @param name Name of the building
     * @param area Floor area of the building
     * @param capacity Maximum capacity of residents
     * @param cost Construction cost
     * @param energy Energy consumption
     * @param districtName Name of the district (default: "Default District")
     * @param neighborhoodName Name of the neighborhood (default: "Default Neighborhood")
     */
    Residential(const std::string &name,
                double area,
                int capacity,
                double cost,
                double energy,
                const std::string &districtName = "Default District",
                const std::string &neighborhoodName = "Default Neighborhood")
        : Building(name, area, capacity, cost)
    {
        this->buildingType = "Residential";
    }

    /**
     * @brief Gets the description of the residential building
     * @return String containing building description
     */
    std::string getDescription() const override
    {
        return "Residential Building: " + getName();
    }

    /**
     * @brief Gets the cost of the building
     * @return The construction cost
     */
    double getCost() const override
    {
        return Cost;
    }

    /**
     * @brief Gets the building type
     * @return String "Residential"
     */
    std::string getBuildingType() const override
    {
        return buildingType;
    }

    /**
     * @brief Gets the floor area of the building
     * @return The floor area in square units
     */
    double getFloorArea() const override
    {
        return floorArea;
    }

    /**
     * @brief Gets the maximum capacity of the building
     * @return Maximum number of residents
     */
    int getMaxCapacity() const override
    {
        return maxCapacity;
    }

    /**
     * @brief Sets the maximum capacity of the building
     * @param capacity New maximum capacity
     */
    void setMaxCapacity(int capacity) override
    {
        maxCapacity = capacity;
    }

    /**
     * @brief Adds a component to the building (not supported)
     * @param component Component to add
     * @throw std::runtime_error Always throws as operation is not supported
     */
    void add(CityComponent *component) override
    {
        throw std::runtime_error("Cannot add components to a Residential building");
    }

    /**
     * @brief Removes a component from the building (not supported)
     * @param component Component to remove
     * @throw std::runtime_error Always throws as operation is not supported
     */
    void remove(CityComponent *component) override
    {
        throw std::runtime_error("Cannot remove components from a Residential building");
    }
};