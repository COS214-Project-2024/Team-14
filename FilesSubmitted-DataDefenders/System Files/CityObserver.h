/**
 * @file CityObserver.h
 * @brief Defines the CityObserver interface for city statistics monitoring
 */
#pragma once

/**
 * @class CityObserver
 * @brief Abstract base class for city statistics observers
 * 
 * Defines interface for objects that monitor city metrics including
 * population, satisfaction, and economic growth.
 */
class CityObserver {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~CityObserver() = default;

    /**
     * @brief Updates observer with new city statistics
     * @param population Current city population
     * @param satisfaction Current satisfaction level
     * @param economicGrowth Current economic growth rate
     */
    virtual void update(int population, double satisfaction, double economicGrowth) = 0;

    /**
     * @brief Displays current statistics
     */
    virtual void display() = 0;
};
