/**
 * @file RoadNetwork.h
 * @brief Defines the RoadNetwork class for managing road infrastructure
 * @inherit Infrastructure
 */
#include "string"
#include "Infrastructure.h"
#include "iostream"
#include "iomanip"

/**
 * @class RoadNetwork
 * @brief Represents road network infrastructure in a city system
 * 
 * This class manages road network infrastructure projects, including their
 * description, cost, and completion status.
 */
class RoadNetwork : public Infrastructure {
private:
    std::string description; ///< Description of the road network
    double cost;            ///< Total cost of the network
    bool isCompleted;       ///< Completion status of the network

public:
    /**
     * @brief Default constructor
     * Initializes a new road network with empty description, zero cost,
     * and incomplete status
     */
    RoadNetwork() : description(""), cost(0.0), isCompleted(false) {}
    
    /**
     * @brief Sets the description of the road network
     * @param desc The description to set
     */
    void setDescription(const std::string& desc) override { description = desc; }

    /**
     * @brief Gets the description of the road network
     * @return The network description
     */
    std::string getDescription() const override { return description; }

    /**
     * @brief Gets the total cost of the network
     * @return The network cost
     */
    double getCost() const override { return cost; }

    /**
     * @brief Sets the cost of the network
     * @param value The cost to set
     */
    void setCost(double value) override { cost = value; }

    /**
     * @brief Gets the type of infrastructure
     * @return String "RoadNetwork"
     */
    std::string getType() const override { return "RoadNetwork"; }
    
    /**
     * @brief Validates the road network
     * @return true if the network has a non-empty description and positive cost
     */
    bool isValid() const override { 
        return !description.empty() && cost > 0; 
    }
    
    /**
     * @brief Creates a deep copy of the road network
     * @return Pointer to the cloned object
     */
    Infrastructure* clone() const override {
        RoadNetwork* copy = new RoadNetwork();
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
     * @return The current completion status
     */
    bool getCompleted() const { return isCompleted; }

    /**
     * @brief Displays detailed information about the road network
     * 
     * Outputs type, description, cost, status, and validation information
     */
    void displayInfo() const override {
        std::cout << "\n=== Road Network Infrastructure ===" << std::endl
                  << "Type: " << getType() << std::endl
                  << "Description: " << description << std::endl
                  << "Cost: $" << std::fixed << std::setprecision(2) << cost << std::endl
                  << "Status: " << (isCompleted ? "Completed" : "In Progress") << std::endl
                  << "Validation: " << (isValid() ? "Valid" : "Invalid") << std::endl;
    }
};