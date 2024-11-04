// HealthDepartment.h
#ifndef HEALTH_DEPARTMENT_H
#define HEALTH_DEPARTMENT_H

#include "GovDepartment.h"
#include "Building.h"

/**
 * @class HealthDepartment
 * @brief Concrete implementation of a government health department
 * 
 * This class represents a health department with its associated building
 * and capital management functionality.
 */
class HealthDepartment : public GovDepartment {
private:
    Building* building;  ///< Pointer to the department's building
    double capital;      ///< Department's capital amount

public:
    /**
     * @brief Constructor for HealthDepartment
     * @param building Pointer to the department's building
     * @param capital Initial capital amount (defaults to 0.0)
     */
    HealthDepartment(Building* building , double capital = 0.0)
        : building(building) {}

    /**
     * @brief Gets the building associated with this health department
     * @return Pointer to the department's building
     */
    Building* getBuilding() override {
        return building;
    }

    /**
     * @brief Gets the department's capital
     * @return The capital amount as a double
     */
    double getCapital() override {
        return capital;
    }

    /**
     * @brief Sets the department's capital
     * @param capital The new capital amount
     */
    void setCapital(double capital) override {
        this->capital = capital;
    }
};

#endif // HEALTH_DEPARTMENT_H