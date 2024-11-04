/**
 * @file WasteManagement.h
 * @brief Waste management utility system
 */

#pragma once
#include "UtilitySystem.h"
#include <unordered_map>

/**
 * @class WasteManagement
 * @brief Manages waste collection and disposal
 * @details Implements resource processing for waste management
 * 
 * @see UtilitySystem
 */
class WasteManagement : public UtilitySystem {
private:
    /**
     * @brief Storage for different resource types and amounts
     */
    std::unordered_map<std::string, int> resourceLevels;
    
public:
    /**
     * @brief Process incoming resources
     * @param resource Resource type identifier
     * @param amount Quantity of resource
     */
    void receiveResources(const std::string& resource, int amount) override {
        resourceLevels[resource] += amount;
    }

    /**
     * @brief Check if resource can be processed
     * @param resource Resource type identifier
     * @return bool True if resource can be processed
     */
    bool canProcessResource(const std::string& resource) const override {
        return resourceLevels.find(resource) != resourceLevels.end();
    }
};