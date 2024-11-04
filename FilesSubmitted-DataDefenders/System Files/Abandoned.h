/**
 * @file Abandoned.h
 * @brief Represents an abandoned building state
 */

#ifndef ABANDONED_H
#define ABANDONED_H

#include "BuildingState.h"

/**
 * @class Abandoned 
 * @brief Concrete state class for abandoned buildings
 * @details Implements the BuildingState interface for abandoned buildings
 * 
 * @see BuildingState
 */

class Abandoned : public BuildingState {
public:

    /**
     * @brief Gets the current state name
     * @return std::string "Abandoned"
     */
    std::string getState() const override {
        return "Abandoned";
    }
};

#endif // ABANDONED_H