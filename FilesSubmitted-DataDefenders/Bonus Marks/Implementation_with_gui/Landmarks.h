/**
 * @file Landmarks.h
 * @brief Defines the Landmarks class for representing landmark buildings in a city
 */

#pragma once
#include "Building.h"
#include <iostream>

/**
 * @class Landmarks
 * @brief Represents landmark buildings in the city
 * 
 * This class inherits from Building and implements specific functionality
 * for landmark structures such as monuments, historic buildings, etc.
 */
class Landmarks : public Building {
public:
    /**
     * @brief Constructs a new Landmarks object
     * @param name Name of the landmark
     * @param area Floor area of the landmark
     * @param capacity Maximum capacity of people
     * @param cost Construction or maintenance cost
     * @param districtName Name of the district (defaults to "Default District")
     * @param neighborhoodName Name of the neighborhood (defaults to "Default Neighborhood")
     */
    Landmarks(const std::string& name, 
             double area, 
             int capacity, 
             double cost,
             const std::string& districtName = "Default District",
             const std::string& neighborhoodName = "Default Neighborhood") 
        : Building(name, area, capacity, cost) 
    {
        this->buildingType = "Landmark";
    }

    /**
     * @brief Gets the description of the landmark
     * @return String containing the landmark's description
     */
    std::string getDescription() const override
    {
        return "Landmark Building: " + getName();
    }

    /**
     * @brief Gets the cost of the landmark
     * @return Cost value in currency units
     */
    double getCost() const override
    {
        return Cost;
    }

    /**
     * @brief Gets the building type
     * @return String indicating the building type ("Landmark")
     */
    std::string getBuildingType() const override
    {
        return buildingType;
    }

    /**
     * @brief Gets the floor area of the landmark
     * @return Floor area in square units
     */
    double getFloorArea() const override
    {
        return floorArea;
    }

    /**
     * @brief Gets the maximum capacity of the landmark
     * @return Maximum number of people the landmark can accommodate
     */
    int getMaxCapacity() const override
    {
        return maxCapacity;
    }

    /**
     * @brief Sets the maximum capacity of the landmark
     * @param capacity New maximum capacity value
     */
    void setMaxCapacity(int capacity) override
    {
        maxCapacity = capacity;
    }

    /**
     * @brief Disabled method - landmarks cannot have components added
     * @param component Unused parameter
     * @throw std::runtime_error Always throws an error as operation is not supported
     */
    void add(CityComponent *) override
    {
        throw std::runtime_error("Cannot add components to a Residential building.");
    }

    /**
     * @brief Disabled method - landmarks cannot have components removed
     * @param component Unused parameter
     * @throw std::runtime_error Always throws an error as operation is not supported
     */
    void remove(CityComponent *) override
    {
        throw std::runtime_error("Cannot remove components from a Residential building.");
    }
};