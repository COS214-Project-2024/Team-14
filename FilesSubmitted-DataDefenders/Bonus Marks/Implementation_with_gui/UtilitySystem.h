#pragma once
#include <string>

/**
 * @file UtilitySystem.h
 * @brief Abstract interface for resource processing utility systems
 */

/**
 * @class UtilitySystem
 * @brief Base interface class for handling and processing resources
 * 
 * This abstract class defines the interface for systems that manage and process
 * different types of resources. Derived classes must implement the resource
 * handling functionality.
 */
class UtilitySystem {
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~UtilitySystem() = default;

    /**
     * @brief Processes incoming resources
     * @param resource The identifier/name of the resource
     * @param amount The quantity of the resource to process
     */
    virtual void receiveResources(const std::string& resource, int amount) = 0;

    /**
     * @brief Checks if a resource type can be processed
     * @param resource The identifier/name of the resource to check
     * @return true if the resource can be processed, false otherwise
     */
    virtual bool canProcessResource(const std::string& resource) const = 0;
};