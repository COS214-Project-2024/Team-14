/**
 * @brief Monitors and manages resource consumption in the city simulation
 * 
 * This class observes population changes and economic growth to calculate
 * resource usage patterns and maintain consumption statistics.
 */
#pragma once
#include "CityObserver.h"
#include "CityResourceDistribution.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

class ResourceConsumption : public CityObserver {
private:
    /** @brief Formatted string containing current resource statistics */
    std::string currentStats;
    
    /** @brief Resource usage per individual citizen */
    double resourceUsagePerCapita;
    
    /** @brief Total resources being consumed by the population */
    double totalResourceConsumption;
    
    /** @brief Pointer to resource distribution system */
    CityResourceDistribution* resourceDistribution;

public:
    /**
     * @brief Constructs a new ResourceConsumption observer
     * @param distribution Pointer to the city's resource distribution system
     * @throw std::invalid_argument if distribution is null
     */
    ResourceConsumption(CityResourceDistribution* distribution) 
        : resourceUsagePerCapita(0.0)
        , totalResourceConsumption(0.0)
        , resourceDistribution(distribution) {
        if (!distribution) {
            throw std::invalid_argument("Resource distribution cannot be null");
        }
    }

    /**
     * @brief Updates resource consumption metrics based on city state
     */
    void update(int population, double satisfaction, double economicGrowth) override {
        if (population < 0) {
            throw std::invalid_argument("Population cannot be negative");
        }

        resourceUsagePerCapita = 1.0 + (economicGrowth * 0.1);
        totalResourceConsumption = population * resourceUsagePerCapita;

        std::stringstream ss;
        ss << "Resource Consumption Stats:\n"
           << "Population: " << population << "\n"
           << "Resource Usage Per Capita: " << std::fixed << std::setprecision(2) 
           << resourceUsagePerCapita << " units\n"
           << "Total Resource Consumption: " << totalResourceConsumption << " units\n"
           << "Economic Growth Impact: " << (economicGrowth * 100) << "% increase in consumption\n"
           << "Total Resources Available: " << resourceDistribution->getTotalResources() << " units";
        currentStats = ss.str();
    }

    /**
     * @brief Displays current resource consumption report
     */
    void display() override {
        std::cout << "\n=== Resource Consumption Report ===\n"
                  << currentStats << "\n"
                  << "=================================\n";
    }

    // Getter methods
    double getResourceUsagePerCapita() const { return resourceUsagePerCapita; }
    double getTotalResourceConsumption() const { return totalResourceConsumption; }
    std::string getCurrentStats() const { return currentStats; }

    /**
     * @brief Virtual destructor for proper cleanup
     */
    virtual ~ResourceConsumption() = default;
};