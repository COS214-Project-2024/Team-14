/**
 * @file TransportationDepartment.h
 * @brief Defines the Transportation Department class within the government structure
 */

#ifndef TRANSPORTATION_DEPARTMENT_H
#define TRANSPORTATION_DEPARTMENT_H

#include "GovDepartment.h"
#include "Building.h"

/**
 * @class TransportationDepartment
 * @brief Represents the Transportation Department in the government structure
 * @inherits GovDepartment
 * 
 * This class manages transportation-related operations and resources,
 * including associated buildings and capital management.
 */
class TransportationDepartment : public GovDepartment {
private:
    Building* building; /**< Pointer to the department's building */
    double Capital;     /**< Available capital for the department */

public:
    /**
     * @brief Constructor that initializes the department with a building
     * @param building Pointer to the department's assigned building
     */
    TransportationDepartment(Building* building)
        : building(building) {}

    /**
     * @brief Gets the department's associated building
     * @return Building* Pointer to the department's building
     */
    Building* getBuilding() override {
        return building;
    }

    /**
     * @brief Gets the department's current capital
     * @return double The amount of available capital
     */
    double getCapital() override {
        return Capital;
    }

    /**
     * @brief Sets the department's capital amount
     * @param Capital The new capital amount to set
     */
    void setCapital(double Capital) override {
        this->Capital = Capital;
    }
};

#endif