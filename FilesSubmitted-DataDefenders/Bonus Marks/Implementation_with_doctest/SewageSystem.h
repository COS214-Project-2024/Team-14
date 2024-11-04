#pragma once
#include "UtilitySystem.h"
#include <unordered_map>

/**
 * @class SewageSystem
 * @brief Implementation of UtilitySystem for sewage processing
 * 
 * Manages and tracks sewage resources using a hash map to store
 * different types of waste materials and their quantities.
 * Inherits from the UtilitySystem base class.
 */
class SewageSystem : public UtilitySystem {
private:
    /** @brief Hash map storing resource types and their current levels */
    std::unordered_map<std::string, int> resourceLevels;
    
public:
    /**
     * @brief Processes and stores incoming sewage resources
     * @param resource The type of sewage resource
     * @param amount The quantity of the resource to process
     * @override Virtual function from UtilitySystem
     */
    void receiveResources(const std::string& resource, int amount) override {
        resourceLevels[resource] += amount;
    }

    /**
     * @brief Checks if a specific type of sewage can be processed
     * @param resource The type of sewage resource to check
     * @return true if the resource exists in the system, false otherwise
     * @override Virtual function from UtilitySystem
     */
    bool canProcessResource(const std::string& resource) const override {
        return resourceLevels.find(resource) != resourceLevels.end();
    }
};