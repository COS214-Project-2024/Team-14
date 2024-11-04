#pragma once
#include "ResourceDistributor.h"
#include "Building.h"
#include <vector>
#include <unordered_map>
#include <iostream>

/**
 * @file CityResourceDistribution.h
 * @brief Resource distribution management system
 */

/**
 * @class CityResourceDistribution
 * @brief Singleton class managing resource distribution across the city
 * @details Handles registration and distribution of resources between utilities and buildings
 * 
 * @see ResourceDistributor
 * @see Building
 * @see UtilitySystem
 */

class CityResourceDistribution : public ResourceDistributor {
private:
    std::unordered_map<std::string, UtilitySystem*> utilities;
    std::vector<Building*> buildings; // Non-owning pointers
    std::unordered_map<std::string, double> totalResources;
    static CityResourceDistribution* instance;
    bool isBeingDestroyed; // Guard against recursive destruction

    // Private constructor for singleton
    CityResourceDistribution() : isBeingDestroyed(false) {}
    
    // Private destructor
    ~CityResourceDistribution() {
        if (!isBeingDestroyed) {
            cleanup();
        }
    }

public:
    CityResourceDistribution(const CityResourceDistribution&) = delete;
    CityResourceDistribution& operator=(const CityResourceDistribution&) = delete;

    static CityResourceDistribution* getInstance() {
        if (!instance) {
            instance = new CityResourceDistribution();
        }
        return instance;
    }

    static void destroyInstance() {
        if (instance) {
            instance->cleanup();
            delete instance;
            instance = nullptr;
        }
    }

    void cleanup() {
        if (isBeingDestroyed) return;
        isBeingDestroyed = true;

        // Clear utilities first
        utilities.clear();

        // Clear other containers
        buildings.clear();
        totalResources.clear();

        isBeingDestroyed = false;
    }

    void registerUtility(const std::string& name, UtilitySystem* system) override {
        if (!system || isBeingDestroyed) return;
        utilities[name] = system; // Store pointer only
    }

    void registerBuilding(Building* building) {
        if (building && std::find(buildings.begin(), buildings.end(), building) == buildings.end()) {
            buildings.push_back(building);
        }
    }

    void distributeResources(const std::string& name, const std::string& resource, int amount) override {
        // Validate input
        if (amount <= 0) {
            std::cout << "Warning: Invalid resource amount " << amount << "\n";
            return;
        }

        // First check if utility exists and can process the resource
        auto utilityIt = utilities.find(name);
        if (utilityIt == utilities.end() || !utilityIt->second->canProcessResource(resource)) {
            std::cout << "Warning: Invalid utility or resource type\n";
            return;
        }

        // Count buildings that need this resource
        std::vector<Building*> needyBuildings;
        for (Building* building : buildings) {
            if (building && building->needsResource(resource)) {
                needyBuildings.push_back(building);
            }
        }

        if (needyBuildings.empty()) {
            std::cout << "No buildings currently need " << resource << "\n";
            return;
        }

        // Update utility's resource level
        utilityIt->second->receiveResources(resource, amount);
        totalResources[resource] += amount;

        // Calculate distribution amount per building
        int sharePerBuilding = amount / needyBuildings.size();
        
        // Distribute to buildings
        std::cout << "\nDistributing " << sharePerBuilding << " units of " << resource 
                  << " to each of " << needyBuildings.size() << " buildings\n";
                  
        for (Building* building : needyBuildings) {
            building->receiveResource(resource, sharePerBuilding);
            std::cout << "Distributed to " << building->getName() 
                      << " - New level: " << building->getResourceLevel(resource) << "\n";
        }
    }

    double getTotalResources() const {
        double total = 0.0;
        for (const auto& [_, amount] : totalResources) {
            total += amount;
        }
        return total;
    }

    double getResourceAmount(const std::string& resource) const {
        auto it = totalResources.find(resource);
        return (it != totalResources.end()) ? it->second : 0.0;
    }

    // For testing/debugging
    size_t getUtilityCount() const {
        return utilities.size();
    }

    size_t getBuildingCount() const {
        return buildings.size();
    }
};

// Initialize static member
CityResourceDistribution* CityResourceDistribution::instance = nullptr;