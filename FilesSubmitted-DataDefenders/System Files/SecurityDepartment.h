/**
 * @file SecurityDepartment.h
 * @brief Header file for the SecurityDepartment class
 * @details Defines a security department within a government organization
 */

#ifndef SECURITY_DEPARTMENT_H
#define SECURITY_DEPARTMENT_H

#include "GovDepartment.h"
#include "Building.h"

/**
 * @class SecurityDepartment
 * @brief Represents a security department that inherits from GovDepartment
 * @details Manages security-related operations and associated building facilities
 */
class SecurityDepartment : public GovDepartment {
private:
    Building* building;  ///< Pointer to the associated building
    double Capital;      ///< Department's capital/budget

public:
    /**
     * @brief Constructs a SecurityDepartment object
     * @param building Pointer to the building assigned to this department
     */
    SecurityDepartment(Building* building)
        : building(building) {}

    /**
     * @brief Gets the associated building
     * @return Pointer to the Building object
     * @override
     */
    Building* getBuilding() override {
        return building;
    }

    /**
     * @brief Gets the department's capital
     * @return Current capital amount as double
     * @override
     */
    double getCapital() override {
        return Capital;
    }

    /**
     * @brief Sets the department's capital
     * @param Capital New capital amount to set
     * @override
     */
    void setCapital(double Capital) override {
        this->Capital = Capital;
    }
};

#endif //SECURITY_DEPARTMENT_H