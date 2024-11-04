// Industrial.h
#pragma once
#include "Building.h"
#include <iostream>

/**
 * @class Industrial
 * @brief Class representing an industrial building
 * 
 * This class implements the Building interface for industrial-type
 * buildings with specific characteristics and behaviors.
 */
class Industrial : public Building
{
public:
    /**
     * @brief Constructor for Industrial building
     * @param name Building name
     * @param area Floor area
     * @param capacity Maximum capacity
     * @param cost Building cost
     * @param districtName District name (defaults to "Default District")
     * @param neighborhoodName Neighborhood name (defaults to "Default Neighborhood")
     */
    Industrial(const std::string &name,
               double area,
               int capacity,
               double cost,
               const std::string &districtName = "Default District",
               const std::string &neighborhoodName = "Default Neighborhood")
        : Building(name, area, capacity, cost)
    {
        this->buildingType = "Industrial";
    }

    /**
     * @brief Gets the building description
     * @return String containing the building description
     */
    std::string getDescription() const override
    {
        return "Industrial Building: " + getName();
    }

    /**
     * @brief Gets the building cost
     * @return The cost as a double
     */
    double getCost() const override
    {
        return Cost;
    }

    /**
     * @brief Gets the building type
     * @return String containing the building type
     */
    std::string getBuildingType() const override
    {
        return buildingType;
    }

    /**
     * @brief Gets the floor area
     * @return The floor area as a double
     */
    double getFloorArea() const override
    {
        return floorArea;
    }

    /**
     * @brief Gets the maximum capacity
     * @return The maximum capacity as an integer
     */
    int getMaxCapacity() const override
    {
        return maxCapacity;
    }

    /**
     * @brief Sets the maximum capacity
     * @param capacity The new maximum capacity
     */
    void setMaxCapacity(int capacity) override
    {
        maxCapacity = capacity;
    }

    /**
     * @brief Adds a component to the building
     * @param component Pointer to the component to add
     * @throws std::runtime_error Cannot add components to an Industrial building
     */
    void add(CityComponent *component) override
    {
        throw std::runtime_error("Cannot add components to an Industrial building.");
    }

    /**
     * @brief Removes a component from the building
     * @param component Pointer to the component to remove
     * @throws std::runtime_error Cannot remove components from an Industrial building
     */
    void remove(CityComponent *component) override
    {
        throw std::runtime_error("Cannot remove components from an Industrial building.");
    }
};
