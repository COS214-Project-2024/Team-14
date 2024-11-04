/** @file UtilityNetworkBuilder.h
 *  @brief Builder class for constructing utility network infrastructure
 */

#pragma once
#include "InfrastructureBuilder.h"
#include "UtilityNetwork.h"
#include <stdexcept>

/**
 * @brief Builder class that constructs UtilityNetwork objects
 * @details Implements the InfrastructureBuilder interface to create utility networks
 */
class UtilityNetworkBuilder : public InfrastructureBuilder {
private:
    /**
     * @brief Validates the internal state of the builder
     * @throws std::runtime_error if no product exists
     */
    void validateState() const {
        if (!product) {
            throw std::runtime_error("No product exists!");
        }
    }

public:
    /**
     * @brief Default constructor
     * @details Initializes the builder and creates a new empty product
     */
    UtilityNetworkBuilder() { reset(); }
    
    /**
     * @brief Destructor
     * @details Cleans up the product if it exists
     */
    ~UtilityNetworkBuilder() {
        if (product) {
            delete product;
        }
    }

    /**
     * @brief Resets the builder to initial state
     * @details Deletes existing product and creates a new empty UtilityNetwork
     */
    void reset() override {
        if (product) {
            delete product;
        }
        product = new UtilityNetwork();
    }

    /**
     * @brief Builds the foundation of the utility network
     * @details Sets up basic description and initial cost
     */
    void BuildFoundation() override {
        reset();
        product->setDescription("Utility Network Foundation");
        product->setCost(800000.0);
    }

    void BuildStructure() override {
        validateState();
        std::string current = product->getDescription();
        product->setDescription(current + " with Utility Infrastructure");
        product->setCost(product->getCost() + 1500000.0);
    }

    void BuildFinishing() override {
        validateState();
        std::string current = product->getDescription();
        product->setDescription(current + " - Completed");
        product->setCost(product->getCost() + 400000.0);
        static_cast<UtilityNetwork*>(product)->setCompleted(true);
    }

    Infrastructure* GetResult() override {
        validateState();
        Infrastructure* result = product;
        product = nullptr;
        return result;
    }

    bool isValidBuild() const override {
        return product && product->isValid();
    }

    double estimateTotalCost() const override {
        return 2700000.0;
    }
};
