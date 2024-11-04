/**
 * @file ResourceDistributor.h
 * @brief Resource distribution system interface
 */

#pragma once
#include <string>
#include <vector>
#include "UtilitySystem.h"
#include "BuildingFactory.h"
#include "Residential.h"
#include "Commercial.h"
#include "Industrial.h"
#include "Landmarks.h"

/**
 * @class ResourceDistributor
 * @brief Abstract interface for resource distribution
 * @details Defines core functionality for resource management
 * 
 * @see UtilitySystem
 * @see BuildingFactory
 */
class ResourceDistributor {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~ResourceDistributor() = default;

    /**
     * @brief Distribute resources to utilities
     * @param name Target utility name
     * @param resource Resource type
     * @param amount Resource quantity
     */
    virtual void distributeResources(const std::string& name, const std::string& resource, int amount) = 0;

    /**
     * @brief Register new utility system
     * @param name Utility system identifier
     * @param system Pointer to utility system
     */
    virtual void registerUtility(const std::string& name, UtilitySystem* system) = 0;
};
