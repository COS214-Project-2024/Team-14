/**
 * @file Worker.h
 * @brief Worker citizen implementation
 */

#pragma once
#include "CitizenPrototype.h"

/**
 * @class Worker
 * @brief Represents working citizens in the city
 * @details Implements worker-specific behaviors and attributes
 * 
 * @see CitizenPrototype
 */
class Worker : public CitizenPrototype {
public:
    /**
     * @brief Constructor
     * @param id Citizen identification number
     * @param salary Initial salary
     */
    Worker(int id, double salary) : CitizenPrototype(id, salary) {}

    /**
     * @brief Destructor
     */
    ~Worker() override = default;
    
    /**
     * @brief Copy constructor
     * @param other Worker to copy
     */
    Worker(const Worker& other) : CitizenPrototype(other) {}
    
    /**
     * @brief Clone the worker
     * @return Worker* Copy of the worker
     */
    CitizenPrototype* clone() const override {
        return new Worker(*this);
    }
    
    /**
     * @brief Get the role of the worker
     * @return std::string Role of the worker
     */
    const std::string getRole() const override {
        return "Worker";
    }
    
    /**
     * @brief Perform the worker's task
     */
    void performTask() override {
        std::cout << "Worker #" << getID() << " is working";
        if (getBuilding()) {
            std::cout << " in the ";
            getBuilding()->print();
        }
        std::cout << "\n";
    }
};
