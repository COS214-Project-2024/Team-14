/**
 * @brief Concrete implementation of the BuildingFactory interface
 * 
 * This factory creates different types of buildings (Residential, Commercial,
 * Industrial, Landmarks) with predefined resource requirements and parameters.
 */
#pragma once
#include "BuildingFactory.h"
#include "Residential.h"
#include "Commercial.h"
#include "Industrial.h"
#include "Landmarks.h"
#include "City.h"
#include "District.h"
#include "Neighborhood.h"
#include "CityResourceDistribution.h"

class ConcreteBuildingFactory : public BuildingFactory {
public:
    /**
     * @brief Creates a new building of the specified type
     * 
     * @param type Type of building to create ("Residential", "Commercial", "Industrial", "Landmark")
     * @param name Name of the building
     * @param area Floor area of the building in square meters
     * @param capacity Maximum occupancy of the building
     * @param cost Construction cost of the building
     * @param districtName Name of the district where building will be located (optional)
     * @param neighborhoodName Name of the neighborhood where building will be located (optional)
     * @return Building* Pointer to the newly created building
     * @throw std::invalid_argument if building type is invalid
     */
    Building* createBuilding(const std::string& type, 
                           const std::string& name, 
                           double area, 
                           int capacity, 
                           double cost,
                           const std::string& districtName = "Default District",
                           const std::string& neighborhoodName = "Default Neighborhood") const override {
        Building* building = nullptr;

        // Create the building based on type
        if (type == "Residential") {
            building = new Residential(name, area, capacity, cost, 100);
            building->setResourceRequirement("electricity", 150); // Match utility resource name
            building->setResourceRequirement("water", 100);
        }
        else if (type == "Commercial") {
            building = new Commercial(name, area, capacity, cost);
            building->setResourceRequirement("electricity", 300);
            building->setResourceRequirement("water", 200);
        }
        else if (type == "Industrial") {
            building = new Industrial(name, area, capacity, cost);
        }
        else if (type == "Landmarks") {
            building = new Landmarks(name, area, capacity, cost);
        }

        if (building) {
            CityResourceDistribution::getInstance()->registerBuilding(building);
            
            // Get or create city (singleton)
            City* city = City::getInstance(); 
            
            // Get or create district
            CityComponent* districtComponent = city->findOrCreateDistrict(districtName);
            District* district = dynamic_cast<District*>(districtComponent);
            
            if (!district) {
                delete building;
                throw std::runtime_error("Failed to create or cast district");
            }
            
            // Get or create neighborhood
            CityComponent* neighborhoodComponent = district->findOrCreateNeighborhood(neighborhoodName);
            Neighborhood* neighborhood = dynamic_cast<Neighborhood*>(neighborhoodComponent);
            
            if (!neighborhood) {
                delete building;
                throw std::runtime_error("Failed to create or cast neighborhood");
            }
            
            // Add building to neighborhood
            neighborhood->add(building);
        }

        return building;
    }
};