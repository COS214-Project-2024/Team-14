/**
 * @file UtilityNetwork.h
 * @brief Defines the UtilityNetwork infrastructure class
 */

#pragma once
#include "Infrastructure.h"
#include <iostream>
#include <iomanip>

/**
 * @class UtilityNetwork
 * @brief Represents a utility network infrastructure system
 * @inherits Infrastructure
 * 
 * This class manages utility network infrastructure, including its description,
 * cost, completion status, and various operations for maintaining and displaying
 * network information.
 */
class UtilityNetwork : public Infrastructure {
private:
    std::string description; /**< Description of the utility network */
    double cost;            /**< Cost of the utility network */
    bool isCompleted;       /**< Completion status of the network */

public:
    /**
     * @brief Default constructor initializing an empty utility network
     */
    UtilityNetwork() : description(""), cost(0.0), isCompleted(false) {}
    
    /**
     * @brief Sets the description of the utility network
     * @param desc The description to set
     */
    void setDescription(const std::string& desc) override { description = desc; }

    /**
     * @brief Gets the description of the utility network
     * @return std::string The current description
     */
    std::string getDescription() const override { return description; }

    /**
     * @brief Gets the cost of the utility network
     * @return double The current cost
     */
    double getCost() const override { return cost; }

    /**
     * @brief Sets the cost of the utility network
     * @param value The cost to set
     */
    void setCost(double value) override { cost = value; }

    /**
     * @brief Gets the type of infrastructure
     * @return std::string The string "UtilityNetwork"
     */
    std::string getType() const override { return "UtilityNetwork"; }
    
    /**
     * @brief Checks if the utility network is valid
     * @return bool True if the network has a description and positive cost
     */
    bool isValid() const override { 
        return !description.empty() && cost > 0; 
    }
    
    /**
     * @brief Creates a deep copy of the utility network
     * @return Infrastructure* Pointer to the cloned network
     */
    Infrastructure* clone() const override {
        UtilityNetwork* copy = new UtilityNetwork();
        copy->description = this->description;
        copy->cost = this->cost;
        copy->isCompleted = this->isCompleted;
        return copy;
    }

    /**
     * @brief Sets the completion status of the network
     * @param completed The completion status to set
     */
    void setCompleted(bool completed) { isCompleted = completed; }

    /**
     * @brief Gets the completion status of the network
     * @return bool True if the network is completed
     */
    bool getCompleted() const { return isCompleted; }

    /**
     * @brief Displays detailed information about the utility network
     * 
     * Outputs formatted information including type, description, cost,
     * completion status, and validation status.
     */
    void displayInfo() const override {
        std::cout << "\n=== Utility Network Infrastructure ===" << std::endl
                  << "Type: " << getType() << std::endl
                  << "Description: " << description << std::endl
                  << "Cost: $" << std::fixed << std::setprecision(2) << cost << std::endl
                  << "Status: " << (isCompleted ? "Completed" : "In Progress") << std::endl
                  << "Validation: " << (isValid() ? "Valid" : "Invalid") << std::endl;
    }
};