/**
 * @file Operational.h
 * @brief Defines the Operational state for buildings
 */

#ifndef OPERATIONAL_H
#define OPERATIONAL_H

#include "BuildingState.h"

/**
 * @class Operational
 * @brief Represents the operational state of a building
 * 
 * This class implements the State pattern, representing when a building
 * is fully operational and functioning normally.
 */
class Operational : public BuildingState {
public:
    /**
     * @brief Gets the current state name
     * @return String "Operational" indicating the building's state
     */
    std::string getState() const override {
        return "Operational";
    }
};

#endif // OPERATIONAL_H