// CitizenPrototype.h
/**
 * @file CitizenPrototype.h
 * @brief Prototype pattern implementation for citizen management
 */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Building;
class IncomeTax;

/**
 * @class CitizenPrototype
 * @brief Abstract base class for different citizen types
 * @details Implements prototype pattern for creating citizen instances
 * 
 * @see Worker
 * @see Student
 * @see Retired
 */
class CitizenPrototype {
protected:
    /**
     * @brief Citizen identification number
     */
    int id;

    /**
     * @brief Citizen's salary or income
     */
    double salary;

    /**
     * @brief Citizen's satisfaction level
     */
    double satisfaction;

    /**
     * @brief Building where citizen is located
     */
    Building* building;

    /**
     * @brief Tax calculator for citizen
     */
    IncomeTax* incomeTax;

public:
    static std::vector<CitizenPrototype*> citizens;
    static int citizenCount;

    /**
     * @brief Constructor
     * @param id Citizen identification number
     * @param salary Initial salary
     */
    CitizenPrototype(int id, double salary);

    /**
     * @brief Virtual destructor
     */
    virtual ~CitizenPrototype();

    /**
     * @brief Copy constructor
     */
    CitizenPrototype(const CitizenPrototype& other);
    
    virtual CitizenPrototype* clone() const = 0;
    virtual const std::string getRole() const = 0;
    virtual void performTask() = 0;
    
    virtual double calculateTotalTax() const;
    virtual double calculateTax() const;
    
    int getID() const { return id; }
    void setID(int newID) { id = newID; }
    double getSalary() const { return salary; }
    virtual void setSalary(double newSalary) { salary = newSalary; }
    
    void setBuilding(Building* b);
    Building* getBuilding() const { return building; }
    
    double getSatisfaction() const { return satisfaction; }
    void updateSatisfaction(double newSatisfaction) { satisfaction = newSatisfaction; }
    
    static int getCitizenCount() { 
        return citizens.size(); 
    }
    
    static void cleanup();

protected:
    CitizenPrototype& operator=(const CitizenPrototype& other);
};