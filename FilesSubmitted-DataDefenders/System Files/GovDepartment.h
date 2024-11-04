// GovDepartment.h
#ifndef GOV_DEPARTMENT_H
#define GOV_DEPARTMENT_H

#include <vector>
#include <string>
#include "Building.h"

/**
 * @class GovDepartment
 * @brief Abstract base class representing a government department
 * 
 * This class defines the interface for government departments in the system.
 * It provides virtual methods for managing sub-departments, accessing the
 * department's building, and managing capital.
 */
class GovDepartment {
public:
    /**
     * @brief Adds a sub-department to this department
     * @param department Pointer to the department to be added
     */
    virtual void addDepartment(GovDepartment* department) {}
    
    /**
     * @brief Removes a sub-department from this department
     * @param department Pointer to the department to be removed
     */
    virtual void removeDepartment(GovDepartment* department) {}
    
    /**
     * @brief Gets the building associated with this department
     * @return Pointer to the department's building
     */
    virtual Building* getBuilding() = 0;
    
    /**
     * @brief Gets the capital allocated to this department
     * @return The capital amount as a double
     */
    virtual double getCapital() = 0;
    
    /**
     * @brief Sets the capital for this department
     * @param capital The new capital amount
     */
    virtual void setCapital(double capital) = 0;
    
    /**
     * @brief Virtual destructor
     */
    virtual ~GovDepartment() = default;
};

#endif //GOV_DEPARTMENT_H