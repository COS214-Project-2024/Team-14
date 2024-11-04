/**
 * @file CompositeGovDepartment.h
 * @brief Implements the Composite pattern for government departments management
 */

#ifndef COMPOSITE_GOV_DEPARTMENT_H
#define COMPOSITE_GOV_DEPARTMENT_H

#include "GovDepartment.h"
#include "Taxation.h"
#include <algorithm>
#include <vector>

/**
 * @class CompositeGovDepartment
 * @brief A composite class that manages multiple government departments
 * @details Implements the Composite design pattern to handle a collection of government departments
 * and manage their capital distribution
 */
class CompositeGovDepartment : public GovDepartment
{
private:
    std::vector<GovDepartment *> departments; ///< Container for child departments
    TaxationPolicy taxPolicy;                 ///< Tax policy for the department
    double totalCapital = 0.0;                ///< Total capital available for distribution

public:
    /**
     * @brief Sets the total capital for the composite department
     * @param Capital The amount of capital to set
     */
    void setCapital(double Capital) override
    {
        totalCapital = Capital;
    }

    /**
     * @brief Gets the current total capital
     * @return Current total capital amount
     */
    double getCapital() override
    {
        return totalCapital;
    }

    /**
     * @brief Distributes capital equally among all child departments
     */
    void distributeCapital()
    {
        if (departments.empty())
            return;

        double capitalPerDepartment = totalCapital / departments.size();
        for (GovDepartment *department : departments)
        {
            department->setCapital(capitalPerDepartment);
        }
    }

    /**
     * @brief Calculates capital per department
     * @param Capital Total capital to be distributed
     * @return Amount of capital per department
     */
    double CalculateCapital(double Capital)
    {
        return Capital / departments.size();
    }

    /**
     * @brief Virtual destructor
     */
    ~CompositeGovDepartment() override = default;

    /**
     * @brief Adds a new department to the composite
     * @param department Pointer to the department to add
     */
    void addDepartment(GovDepartment *department) override
    {
        if (department)
        {
            departments.push_back(department);
            distributeCapital();
        }
    }

    /**
     * @brief Removes a department from the composite
     * @param department Pointer to the department to remove
     */
    void removeDepartment(GovDepartment *department) override
    {
        auto it = std::find(departments.begin(), departments.end(), department);
        if (it != departments.end())
        {
            departments.erase(it);
            distributeCapital();
        }
    }

    /**
     * @brief Gets the associated building
     * @return nullptr as composite departments don't have direct building associations
     */
    Building *getBuilding() override
    {
        return nullptr;
    }

    /**
     * @brief Gets the total number of departments
     * @return Number of departments in the composite
     */
    size_t getDepartmentCount() const
    {
        return departments.size();
    }

    /**
     * @brief Gets the vector of department pointers
     * @return Constant reference to the departments vector
     */
    const std::vector<GovDepartment *> &getDepartments() const
    {
        return departments;
    }
};

#endif // COMPOSITE_GOV_DEPARTMENT_H