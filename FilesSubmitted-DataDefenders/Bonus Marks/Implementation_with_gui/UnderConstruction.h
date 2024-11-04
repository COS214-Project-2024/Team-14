/**
 * @file UnderConstruction.h
 * @brief Defines the UnderConstruction state for buildings
 */

#ifndef UNDER_CONSTRUCTION_H
#define UNDER_CONSTRUCTION_H

#include "BuildingState.h"

/**
 * @class UnderConstruction
 * @brief Represents the under construction state of a building
 * @inherits BuildingState
 * 
 * This class implements the State pattern to represent a building
 * that is currently under construction.
 */
class UnderConstruction : public BuildingState {
public:
    /**
     * @brief Gets the current state description
     * @return std::string The string "Under Construction"
     */
    std::string getState() const override {
        return "Under Construction";
    }
};

#endif // UNDER_CONSTRUCTION_H