// CityPlanner.h
#pragma once
#include "InfrastructureBuilder.h"
#include <vector>
#include <memory>
#include <stdexcept>
#include "ModernTransport.h"
#include "LegacyTransportSystem.h"
#include "TransportSystemAdapter.h"
#include "TransportFactory.h"

/**
 * @file CityPlanner.h
 * @brief Infrastructure and city planning management
 */

/**
 * @class CityPlanner
 * @brief Manages infrastructure construction and transport system integration
 * @details Coordinates between different infrastructure builders and transport systems
 * 
 * @see InfrastructureBuilder
 * @see ModernTransport
 * @see TransportSystemAdapter
 */
class CityPlanner {
private:
    /**
     * @brief List of completed infrastructure projects
     */
    std::vector<Infrastructure*> completedProjects;

    /**
     * @brief List of transport systems
     */
    std::vector<ModernTransport*> transportSystems;

public:
    /**
     * @brief Destructor
     * @details Cleans up all projects and transport systems
     */
    ~CityPlanner() {
        for (auto project : completedProjects) {
            delete project;
        }
        for (auto transport : transportSystems) {
            delete transport;
        }
    }

    /**
     * @brief Constructs new infrastructure
     * @param builder Infrastructure builder to use
     * @return Infrastructure* Pointer to completed infrastructure
     * @throw std::runtime_error If build is invalid
     */
    Infrastructure* constructInfrastructure(InfrastructureBuilder& builder) {
        builder.reset();
        builder.BuildFoundation();
        builder.BuildStructure();
        builder.BuildFinishing();
        
        if (!builder.isValidBuild()) {
            throw std::runtime_error("Invalid build state!");
        }
        
        Infrastructure* result = builder.GetResult();
        completedProjects.push_back(result);
        return result;
    }

    double estimateProjectCost(InfrastructureBuilder& builder) {
        return builder.estimateTotalCost();
    }

    void clearProjects() {
        for (auto project : completedProjects) {
            delete project;
        }
        completedProjects.clear();
    }

    const std::vector<Infrastructure*>& getCompletedProjects() const {
        return completedProjects;
    }

    ModernTransport* integrateTransportSystem(const std::string& type) {
        ModernTransport* transport = TransportFactory::createTransport(type);
        if (transport) {
            transportSystems.push_back(transport);
        }
        return transport;
    }

    ModernTransport* adaptLegacyTransport(LegacyTransportSystem* legacySystem) {
        ModernTransport* adapted = TransportFactory::adaptLegacyTransport(legacySystem);
        if (adapted) {
            transportSystems.push_back(adapted);
        }
        return adapted;
    }

    const std::vector<ModernTransport*>& getTransportSystems() const {
        return transportSystems;
    }
};
