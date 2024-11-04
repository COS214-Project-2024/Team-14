/**
 * @file District.h
 * @brief City district management
 */

#pragma once
#include "CityComponent.h"
#include "Neighborhood.h"
#include <string>
#include <vector>

/**
 * @class District
 * @brief Represents a city district containing neighborhoods
 * @details Implements composite pattern for city organization
 * 
 * @see CityComponent
 * @see Neighborhood
 */
class District : public CityComponent
{
private:
    std::string name;
    std::vector<CityComponent *> neighborhoods;

public:
    /**
     * @brief Constructor
     * @param districtName Name of the district
     */
    District(const std::string &districtName) : name(districtName) {}

    /**
     * @brief Destructor
     * @details Cleans up all neighborhoods
     */
    ~District()
    {
        for (auto *neighborhood : neighborhoods)
        {
            delete neighborhood;
        }
        neighborhoods.clear();
    }

    /**
     * @brief Add neighborhood to district
     * @param component Neighborhood to add
     */
    void add(CityComponent *component) override
    {
        neighborhoods.push_back(component);
    }

    /**
     * @brief Remove neighborhood from district
     * @param component Neighborhood to remove
     */
    void remove(CityComponent *component) override
    {
        auto it = std::find(neighborhoods.begin(), neighborhoods.end(), component);
        if (it != neighborhoods.end())
        {
            neighborhoods.erase(it);
        }
    }

    /**
     * @brief Get district name
     * @return std::string District name
     */
    std::string getName() const override
    {
        return name;
    }

    std::vector<CityComponent *> getComponents() const override
    {
        return neighborhoods;
    }

    CityComponent *findComponent(const std::string &name) override
    {
        for (auto *neighborhood : neighborhoods)
        {
            if (neighborhood->getName() == name)
            {
                return neighborhood;
            }
        }
        return nullptr;
    }

    CityComponent *findOrCreateNeighborhood(const std::string &neighborhoodName)
    {
        CityComponent *existingNeighborhood = findComponent(neighborhoodName);
        if (existingNeighborhood)
        {
            return existingNeighborhood;
        }

        Neighborhood *newNeighborhood = new Neighborhood(neighborhoodName);
        add(newNeighborhood);
        return newNeighborhood;
    }

    void print(int indent = 0) const override
    {
        std::string indentation(indent, ' ');
        std::cout << indentation << "District: " << name << "\n";
        for (auto *neighborhood : neighborhoods)
        {
            if (Neighborhood *n = dynamic_cast<Neighborhood *>(neighborhood))
            {
                n->print(indent + 2);
            }
        }
    }
};