/**
 * @file EducationDepartment.h
 * @brief Implements the Education Department functionality
 */

#ifndef EDUCATION_DEPARTMENT_H
#define EDUCATION_DEPARTMENT_H

#include "GovDepartment.h"
#include "Building.h"

/**
 * @class EducationDepartment
 * @brief Represents the Education Department in the government structure
 * @details Manages educational facilities and their associated capital
 */
class EducationDepartment : public GovDepartment {
private:
    Building* building;  ///< Associated building for the department
    double Capital;      ///< Department's capital amount

public:
    /**
     * @brief Constructor
     * @param building Pointer to the associated building
     */
    EducationDepartment(Building* building)
        : building(building) {}

    /**
     * @brief Gets the associated building
     * @return Pointer to the department's building
     */
    Building* getBuilding() override {
        return building;
    }

    /**
     * @brief Gets the department's capital
     * @return Current capital amount
     */
    double getCapital() override {
        return Capital;
    }

    /**
     * @brief Sets the department's capital
     * @param Capital New capital amount to set
     */
    void setCapital(double Capital) override {
        this->Capital = Capital;
    }
};

#endif //EDUCATION_DEPARTMENT_H