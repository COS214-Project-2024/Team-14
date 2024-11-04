/**
 * @file EconomicGrowth.h
 * @brief Implements economic growth monitoring and analysis
 */

#pragma once
#include "CityObserver.h"
#include <string>
#include <sstream>
#include <iostream>

/**
 * @class EconomicGrowth
 * @brief Observer class for monitoring economic growth metrics
 * @details Implements the Observer pattern to track and analyze economic indicators
 */
class EconomicGrowth : public CityObserver {
private:
    std::string currentStats;  ///< Current statistics formatted as string
    double gdpPerCapita;      ///< GDP per capita
    double growthRate;        ///< Current growth rate
    double projectedGrowth;   ///< Projected future growth rate

public:
    /**
     * @brief Default constructor
     * @details Initializes all economic metrics to 0.0
     */
    EconomicGrowth() : gdpPerCapita(0.0), growthRate(0.0), projectedGrowth(0.0) {}

    /**
     * @brief Updates economic metrics based on new city statistics
     * @param population Current city population
     * @param satisfaction Current satisfaction level
     * @param economicGrowth Current economic growth rate
     */
    void update(int population, double satisfaction, double economicGrowth) override {
        // Calculate economic metrics based on current stats
        gdpPerCapita = 50000.0 * (1.0 + economicGrowth);
        growthRate = economicGrowth * 100;
        projectedGrowth = economicGrowth * (1.0 + (satisfaction / 100.0));

        std::stringstream ss;
        ss << "Economic Analysis:\n"
           << "GDP per Capita: $" << gdpPerCapita << "\n"
           << "Current Growth Rate: " << growthRate << "%\n"
           << "Satisfaction Impact on Growth: " << (satisfaction / 100.0) << "\n"
           << "Projected Growth Rate: " << (projectedGrowth * 100) << "%";
        currentStats = ss.str();
    }

    /**
     * @brief Displays the current economic statistics
     */
    void display() override {
        std::cout << "\n=== Economic Growth Report ===\n"
                  << currentStats << "\n"
                  << "============================\n";
    }
};