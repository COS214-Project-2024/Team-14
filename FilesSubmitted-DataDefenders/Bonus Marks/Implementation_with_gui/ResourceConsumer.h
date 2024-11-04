/**
 * @file ResourceConsumer.h
 * @brief Interface for resource consuming entities
 */

#pragma once
#include <string>
#include <unordered_map>

/**
 * @class ResourceConsumer
 * @brief Abstract interface for entities that consume resources
 * @details Defines standard interface for resource consumption management
 */
class ResourceConsumer {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~ResourceConsumer() = default;

    /**
     * @brief Receive resource allocation
     * @param resource Type of resource
     * @param amount Quantity received
     */
    virtual void receiveResource(const std::string& resource, int amount) = 0;

    /**
     * @brief Get current resource level
     * @param resource Type of resource
     * @return int Current amount of resource
     */
    virtual int getResourceLevel(const std::string& resource) const = 0;

    /**
     * @brief Check if resource is needed
     * @param resource Type of resource
     * @return bool True if resource is needed
     */
    virtual bool needsResource(const std::string& resource) const = 0;
};