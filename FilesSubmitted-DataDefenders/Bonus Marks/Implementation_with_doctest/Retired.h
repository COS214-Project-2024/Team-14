/**
 * @file Retired.h
 * @brief Defines the Retired class for managing retired citizens
 * @inherit CitizenPrototype
 */
#pragma once
#include "CitizenPrototype.h"

/**
 * @class Retired
 * @brief Represents a retired citizen in the city system
 * 
 * This class manages retired citizens, including their pension
 * and daily activities.
 */
class Retired : public CitizenPrototype {
public:
    /**
     * @brief Constructor for creating a retired citizen
     * @param id Unique identifier for the citizen
     * @param pension Monthly pension amount
     */
    Retired(int id, double pension) : CitizenPrototype(id, pension) {}
    
    /**
     * @brief Virtual destructor
     */
    ~Retired() override = default;
    
    /**
     * @brief Copy constructor
     * @param other The Retired object to copy from
     */
    Retired(const Retired& other) : CitizenPrototype(other) {}
    
    /**
     * @brief Creates a clone of the retired citizen
     * @return Pointer to the cloned object
     */
    CitizenPrototype* clone() const override {
        return new Retired(*this);
    }
    
    /**
     * @brief Gets the role of the citizen
     * @return String "Retired"
     */
    const std::string getRole() const override {
        return "Retired";
    }
    
    /**
     * @brief Performs the daily task of the retired citizen
     * Outputs the current activity and location
     */
    void performTask() override {
        std::cout << "Retired person #" << getID() << " is resting";
        if (getBuilding()) {
            std::cout << " in the ";
            getBuilding()->print();
        }
        std::cout << "\n";
    }
    
    /**
     * @brief Attempts to set salary (not supported for retired citizens)
     * @param newSalary The new salary value (ignored)
     */
    void setSalary(double newSalary) override {
        std::cout << "You cannot modify pension for retired person #" << getID() 
                 << ". Pension is fixed at $" << getSalary() << std::endl;
    }
    
    /**
     * @brief Gets the pension amount
     * @return Current pension amount
     */
    double getPension() const {
        return getSalary();
    }
};
