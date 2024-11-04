/**
 * @file InfrastructureBuilder.h
 * @brief Abstract builder class for creating infrastructure objects
 */

#pragma once
#include "Infrastructure.h"

/**
 * @class InfrastructureBuilder
 * @brief Abstract builder class that defines the interface for constructing Infrastructure objects
 * 
 * This class implements the Builder design pattern for creating Infrastructure objects
 * in a step-by-step manner.
 */
class InfrastructureBuilder {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~InfrastructureBuilder() = default;

    /**
     * @brief Resets the builder to its initial state
     */
    virtual void reset() = 0;

    /**
     * @brief Builds the foundation of the infrastructure
     */
    virtual void BuildFoundation() = 0;

    /**
     * @brief Builds the main structure
     */
    virtual void BuildStructure() = 0;

    /**
     * @brief Applies finishing touches to the infrastructure
     */
    virtual void BuildFinishing() = 0;

    /**
     * @brief Returns the constructed Infrastructure object
     * @return Pointer to the constructed Infrastructure object
     */
    virtual Infrastructure* GetResult() = 0;

    /**
     * @brief Checks if the current build configuration is valid
     * @return true if the build is valid, false otherwise
     */
    virtual bool isValidBuild() const = 0;

    /**
     * @brief Estimates the total cost of the infrastructure
     * @return Estimated cost in currency units
     */
    virtual double estimateTotalCost() const = 0;

protected:
    Infrastructure* product = nullptr; ///< Pointer to the infrastructure being built
};