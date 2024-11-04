/**
 * @file Commercial.h
 * @brief Commercial building implementation
 */

#pragma once
#include "Building.h"
#include <iostream>

/**
 * @class Commercial
 * @brief Represents commercial buildings in the city
 * @details Handles commercial-specific building attributes and behaviors
 * 
 * @see Building
 */
class Commercial : public Building {
public:
    /**
     * @brief Constructor for commercial building
     * @param name Building name
     * @param area Floor area in square meters
     * @param capacity Maximum occupancy
     * @param cost Construction cost
     * @param districtName District location
     * @param neighborhoodName Neighborhood location
     */
    Commercial(const std::string& name, double area, int capacity, double cost,
              const std::string& districtName = "Default District",
              const std::string& neighborhoodName = "Default Neighborhood")
        : Building(name, area, capacity, cost)
    {
        this->buildingType = "Commercial";
    }

    /**
     * @brief Get building description
     * @return std::string Commercial building description
     */
    std::string getDescription() const override
    {
        return "Commercial Building: " + getName();
    }

    /**
     * @brief Get building cost
     * @return double Construction cost
     */
    double getCost() const override
    {
        return Cost;
    }

    /**
     * @brief Get building type
     * @return std::string "Commercial"
     */
    std::string getBuildingType() const override
    {
        return buildingType;
    }

    /**
     * @brief Get floor area
     * @return double Floor area in square meters
     */
    double getFloorArea() const override
    {
        return floorArea;
    }

    /**
     * @brief Get maximum capacity
     * @return int Maximum occupancy
     */
    int getMaxCapacity() const override
    {
        return maxCapacity;
    }

    /**
     * @brief Set maximum capacity
     * @param capacity New maximum occupancy
     */
    void setMaxCapacity(int capacity) override
    {
        maxCapacity = capacity;
    }

    void add(CityComponent *component) override
    {
        throw std::runtime_error("Cannot add components to a Commercial building");
    }

    void remove(CityComponent *component) override
    {
        throw std::runtime_error("Cannot remove components from a Commercial building");
    }
};
