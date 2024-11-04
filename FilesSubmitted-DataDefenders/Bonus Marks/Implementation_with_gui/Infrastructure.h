// Infrastructure.h
#pragma once
#include <string>

/**
 * @class Infrastructure
 * @brief Abstract base class for infrastructure components
 * 
 * This class defines the interface for all infrastructure components
 * in the system, providing methods for description, cost management,
 * type identification, and validation.
 */
class Infrastructure {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Infrastructure() = default;
    
    /**
     * @brief Sets the infrastructure description
     * @param desc The new description
     */
    virtual void setDescription(const std::string& desc) = 0;
    
    /**
     * @brief Gets the infrastructure description
     * @return String containing the description
     */
    virtual std::string getDescription() const = 0;
    
    /**
     * @brief Gets the infrastructure cost
     * @return The cost as a double
     */
    virtual double getCost() const = 0;
    
    /**
     * @brief Sets the infrastructure cost
     * @param cost The new cost
     */
    virtual void setCost(double cost) = 0;
    
    /**
     * @brief Gets the infrastructure type
     * @return String containing the type
     */
    virtual std::string getType() const = 0;
    
    /**
     * @brief Creates a clone of the infrastructure
     * @return Pointer to the cloned Infrastructure object
     */
    virtual Infrastructure* clone() const = 0;
    
    /**
     * @brief Checks if the infrastructure is valid
     * @return true if valid, false otherwise
     */
    virtual bool isValid() const = 0;
    
    /**
     * @brief Displays information about the infrastructure
     */
    virtual void displayInfo() const = 0;
};