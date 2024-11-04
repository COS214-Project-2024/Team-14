/**
 * @file PublicTransitBuilder.h
 * @brief Defines the PublicTransitBuilder class for constructing public transit infrastructure
 * @inherit InfrastructureBuilder
 */
#pragma once
#include "InfrastructureBuilder.h"
#include "PublicTransit.h"
#include <stdexcept>

/**
 * @class PublicTransitBuilder
 * @brief Builder class for constructing PublicTransit objects
 * 
 * Implements the Builder pattern to construct PublicTransit infrastructure
 * in a step-by-step manner.
 */
class PublicTransitBuilder : public InfrastructureBuilder {
private:
    /**
     * @brief Validates the current state of the builder
     * @throw std::runtime_error if no product exists
     */
    void validateState() const {
        if (!product) {
            throw std::runtime_error("No product exists!");
        }
    }

public:
    /**
     * @brief Default constructor
     * Initializes the builder and creates a new product
     */
    PublicTransitBuilder() { reset(); }
    
    /**
     * @brief Destructor
     * Cleans up any allocated product
     */
    ~PublicTransitBuilder() {
        if (product) {
            delete product;
        }
    }

    /**
     * @brief Resets the builder to initial state
     * Creates a new PublicTransit object
     */
    void reset() override {
        if (product) {
            delete product;
        }
        product = new PublicTransit();
    }

    /**
     * @brief Builds the foundation of the public transit infrastructure
     * Sets initial description and base cost
     */
    void BuildFoundation() override {
        reset();
        product->setDescription("Public Transit Foundation");
        product->setCost(1000000.0);
    }

    /**
     * @brief Builds the main structure of the public transit infrastructure
     * Adds to the description and increases cost
     */
    void BuildStructure() override {
        validateState();
        std::string current = product->getDescription();
        product->setDescription(current + " with Transit Infrastructure");
        product->setCost(product->getCost() + 2000000.0);
    }

    /**
     * @brief Applies finishing touches to the public transit infrastructure
     * Completes the description, adds final costs, and marks as completed
     */
    void BuildFinishing() override {
        validateState();
        std::string current = product->getDescription();
        product->setDescription(current + " - Completed");
        product->setCost(product->getCost() + 500000.0);
        static_cast<PublicTransit*>(product)->setCompleted(true);
    }

    /**
     * @brief Returns the constructed product and resets the builder
     * @return Pointer to the completed Infrastructure object
     */
    Infrastructure* GetResult() override {
        validateState();
        Infrastructure* result = product;
        product = nullptr;
        return result;
    }

    /**
     * @brief Checks if the current build is valid
     * @return true if the product exists and is valid
     */
    bool isValidBuild() const override {
        return product && product->isValid();
    }

    /**
     * @brief Estimates the total cost of the project
     * @return Estimated total cost (3.5 million)
     */
    double estimateTotalCost() const override {
        return 3500000.0; // Base estimation
    }
};
