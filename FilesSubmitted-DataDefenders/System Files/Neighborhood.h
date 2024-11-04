/**
 * @file Neighborhood.h
 * @brief Defines the Neighborhood class for managing city neighborhoods
 */

#pragma once
#include "CityComponent.h"
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

/**
 * @class Neighborhood
 * @brief Represents a neighborhood in the city
 * 
 * This class implements the Composite pattern as part of the city structure,
 * managing a collection of buildings and other city components.
 */
class Neighborhood : public CityComponent
{
private:
    std::string name;                            ///< Name of the neighborhood
    std::vector<CityComponent *> buildings;      ///< Collection of buildings in the neighborhood
    std::vector<CityComponent *> components;     ///< Collection of other components
    double population;                           ///< Population of the neighborhood
    double area;                                 ///< Total area of the neighborhood

public:
    /**
     * @brief Constructs a new Neighborhood object
     * @param neighborhoodName Name of the neighborhood
     */
    Neighborhood(const std::string &neighborhoodName) : name(neighborhoodName) {}

    /**
     * @brief Destructor
     * 
     * Clears the buildings vector without deleting the buildings themselves,
     * as they are managed elsewhere.
     */
    ~Neighborhood()
    {
        buildings.clear();
    }

    /**
     * @brief Adds a component to the neighborhood
     * @param component Pointer to the component to add
     */
    void add(CityComponent *component) override
    {
        buildings.push_back(component);
    }

    /**
     * @brief Removes a component from the neighborhood
     * @param component Pointer to the component to remove
     */
    void remove(CityComponent *component) override
    {
        auto it = std::find(buildings.begin(), buildings.end(), component);
        if (it != buildings.end())
        {
            buildings.erase(it);
        }
    }

    /**
     * @brief Gets the name of the neighborhood
     * @return String containing the neighborhood name
     */
    std::string getName() const override
    {
        return name;
    }

    /**
     * @brief Gets all components in the neighborhood
     * @return Vector of pointers to all components
     */
    std::vector<CityComponent *> getComponents() const override
    {
        return buildings;
    }

    /**
     * @brief Finds a component by name
     * @param name Name of the component to find
     * @return Pointer to the found component, or nullptr if not found
     */
    CityComponent *findComponent(const std::string &name) override
    {
        for (auto *building : buildings)
        {
            if (building->getName() == name)
            {
                return building;
            }
        }

        return nullptr;
    }

    /**
     * @brief Prints the neighborhood structure
     * @param indent Number of spaces to indent (default: 0)
     */
    void print(int indent = 0) const override
    {
        std::string indentation(indent, ' ');
        std::cout << indentation << "Neighborhood: " << name << "\n";
        for (auto *building : buildings)
        {
            std::cout << indentation << "  Building: " << building->getName()
                      << " (Type: " << building->getBuildingType() << ")\n";
        }
    }
};