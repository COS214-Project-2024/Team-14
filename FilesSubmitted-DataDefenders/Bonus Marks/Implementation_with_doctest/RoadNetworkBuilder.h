/**
 * @file RoadNetworkBuilder.h
 * @brief Concrete builder class for constructing road network infrastructure
 */

#pragma once
#include "InfrastructureBuilder.h"
#include "RoadNetwork.h"
#include <stdexcept>

/**
 * @class RoadNetworkBuilder
 * @brief A builder class responsible for constructing road network infrastructure
 * @inherits InfrastructureBuilder
 * 
 * This class implements the Builder pattern for creating road networks in a step-by-step manner,
 * managing the construction process through foundation, structure, and finishing phases.
 */
class RoadNetworkBuilder : public InfrastructureBuilder {
private:
    /**
     * @brief Validates the current state of the builder
     * @throws std::runtime_error if no product exists
     */
    void validateState() const {
        if (!product) {
            throw std::runtime_error("No product exists!");
        }
    }

public:
    /**
     * @brief Default constructor that initializes a new road network
     */
    RoadNetworkBuilder() { reset(); }
    
    /**
     * @brief Destructor that ensures proper cleanup of the product
     */
    ~RoadNetworkBuilder() {
        if (product) {
            delete product;
        }
    }

    /**
     * @brief Resets the builder to initial state with a new road network
     */
    void reset() override {
        if (product) {
            delete product;
        }
        product = new RoadNetwork();
    }

    /**
     * @brief Builds the foundation phase of the road network
     * 
     * Sets the initial description and base cost for the foundation
     */
    void BuildFoundation() override {
        reset();
        product->setDescription("Road Network Foundation");
        product->setCost(1500000.0);
    }

    /**
     * @brief Builds the structural phase of the road network
     * 
     * Adds road infrastructure and updates the cost accordingly
     */
    void BuildStructure() override {
        validateState();
        std::string current = product->getDescription();
        product->setDescription(current + " with Road Infrastructure");
        product->setCost(product->getCost() + 2500000.0);
    }

    /**
     * @brief Completes the finishing phase of the road network
     * 
     * Finalizes the construction and marks the network as completed
     */
    void BuildFinishing() override {
        validateState();
        std::string current = product->getDescription();
        product->setDescription(current + " - Completed");
        product->setCost(product->getCost() + 800000.0);
        static_cast<RoadNetwork*>(product)->setCompleted(true);
    }

    /**
     * @brief Returns the constructed road network
     * @return Infrastructure* Pointer to the completed infrastructure
     * @note Transfers ownership of the product to the caller
     */
    Infrastructure* GetResult() override {
        validateState();
        Infrastructure* result = product;
        product = nullptr;
        return result;
    }

    /**
     * @brief Checks if the current build state is valid
     * @return bool True if the build is valid, false otherwise
     */
    bool isValidBuild() const override {
        return product && product->isValid();
    }

    /**
     * @brief Estimates the total cost of the road network construction
     * @return double The estimated total cost in currency units
     */
    double estimateTotalCost() const override {
        return 4800000.0;
    }
};