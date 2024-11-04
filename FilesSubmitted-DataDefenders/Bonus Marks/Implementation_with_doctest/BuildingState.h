//BuildingState.h
#ifndef BUILDING_STATE_H
#define BUILDING_STATE_H

#include <string>

/**
 * @file BuildingState.h
 * @brief State pattern for building management
 */

/**
 * @class BuildingState
 * @brief Abstract base class for building states
 * @details Implements state pattern for managing building lifecycle
 * 
 * @see Operational
 * @see UnderConstruction
 * @see Abandoned
 */
class BuildingState {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~BuildingState() = default;

    /**
     * @brief Get current state name
     * @return std::string Name of the current state
     */
    virtual std::string getState() const = 0;
};

#endif // BUILDING_STATE_H