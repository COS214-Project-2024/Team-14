/**
 * @file PublicTransit.h
 * @brief Defines the PublicTransit class for managing public transportation infrastructure
 * @inherit Infrastructure
 */
#pragma once
#include "Infrastructure.h"
#include <iostream>
#include <iomanip>

/**
 * @class PublicTransit
 * @brief Represents public transit infrastructure in a city system
 * 
 * This class manages public transit infrastructure projects, including their description,
 * cost, and completion status.
 */
class PublicTransit : public Infrastructure {
private:
    std::string description; ///< Description of the public transit project
    double cost;            ///< Total cost of the project
    bool isCompleted;       ///< Completion status of the project

public:
    /**
     * @brief Default constructor
     * Initializes a new public transit project with empty description, zero cost,
     * and incomplete status
     */
    PublicTransit() : description(""), cost(0.0), isCompleted(false) {}
    
    /**
     * @brief Sets the description of the public transit project
     * @param desc The description to set
     */
    void setDescription(const std::string& desc) override { description = desc; }

    /**
     * @brief Gets the description of the public transit project
     * @return The project description
     */
    std::string getDescription() const override { return description; }

    /**
     * @brief Gets the total cost of the project
     * @return The project cost
     */
    double getCost() const override { return cost; }

    /**
     * @brief Sets the cost of the project
     * @param value The cost to set
     */
    void setCost(double value) override { cost = value; }

    /**
     * @brief Gets the type of infrastructure
     * @return String "PublicTransit"
     */
    std::string getType() const override { return "PublicTransit"; }
    
    /**
     * @brief Validates the public transit project
     * @return true if the project has a non-empty description and positive cost
     */
    bool isValid() const override { 
        return !description.empty() && cost > 0; 
    }
    
    /**
     * @brief Creates a deep copy of the public transit project
     * @return Pointer to the cloned object
     */
    Infrastructure* clone() const override {
        PublicTransit* copy = new PublicTransit();
        copy->description = this->description;
        copy->cost = this->cost;
        copy->isCompleted = this->isCompleted;
        return copy;
    }

    /**
     * @brief Sets the completion status of the project
     * @param completed The completion status to set
     */
    void setCompleted(bool completed) { isCompleted = completed; }

    /**
     * @brief Gets the completion status of the project
     * @return The current completion status
     */
    bool getCompleted() const { return isCompleted; }

    /**
     * @brief Displays detailed information about the public transit project
     * 
     * Outputs type, description, cost, status, and validation information
     */
    void displayInfo() const override {
        std::cout << "\n=== Public Transit Infrastructure ===" << std::endl
                  << "Type: " << getType() << std::endl
                  << "Description: " << description << std::endl
                  << "Cost: $" << std::fixed << std::setprecision(2) << cost << std::endl
                  << "Status: " << (isCompleted ? "Completed" : "In Progress") << std::endl
                  << "Validation: " << (isValid() ? "Valid" : "Invalid") << std::endl;
    }
};