/**
 * @file CityStats.h
 * @brief Defines the CityStats class for managing city statistics observers
 */
#pragma once
#include <vector>
#include <algorithm>
#include "CityObserver.h"

/**
 * @class CityStats
 * @brief Manages collection of city statistics observers
 * 
 * Implements the Subject role in the Observer pattern, maintaining
 * a list of observers and notifying them of changes in city statistics.
 */
class CityStats {
private:
    std::vector<CityObserver*> observers;  ///< Collection of registered observers

public:
    /**
     * @brief Virtual destructor
     */
    virtual ~CityStats() = default;
    
    /**
     * @brief Registers a new observer
     * @param observer Pointer to observer to register
     */
    void attach(CityObserver* observer) {
        if (observer != nullptr) {
            observers.push_back(observer);
        }
    }
    
    /**
     * @brief Removes a registered observer
     * @param observer Pointer to observer to remove
     */
    void detach(CityObserver* observer) {
        if (observer != nullptr) {
            observers.erase(
                std::remove(observers.begin(), observers.end(), observer),
                observers.end()
            );
        }
    }

protected:
    /**
     * @brief Notifies all observers of updates to city statistics
     * @param population Current city population
     * @param satisfaction Current satisfaction level
     * @param economicGrowth Current economic growth rate
     */
    void notify(int population, double satisfaction, double economicGrowth) {
        for (auto& observer : observers) {
            if (observer != nullptr) {
                observer->update(population, satisfaction, economicGrowth);
            }
        }
    }
};