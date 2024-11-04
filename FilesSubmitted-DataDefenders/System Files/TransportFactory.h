/**
 * @file TransportFactory.h
 * @brief Factory for transport system creation
 */

#pragma once
#include "ModernTransport.h"
#include "LegacyTransportSystem.h"
#include "TransportSystemAdapter.h"
#include <vector>

/**
 * @class TransportFactory
 * @brief Creates and manages transport system instances
 * @details Implements factory pattern for transport system creation
 * 
 * @see ModernTransport
 * @see LegacyTransportSystem
 */
class TransportFactory {
private:
    /**
     * @brief Collection of legacy transport systems
     */
    static std::vector<LegacyTransportSystem*> legacySystems;

public:
    /**
     * @brief Create a new transport system
     * @param type Type of transport system to create
     * @return ModernTransport* Pointer to new transport system
     */
    static ModernTransport* createTransport(const std::string& type) {
        if (type == "modern") {
            return new ModernTransport();
        } else if (type == "legacy") {
            LegacyTransportSystem* legacySystem = new LegacyTransportSystem();
            legacySystems.push_back(legacySystem);
            return new TransportSystemAdapter(legacySystem);
        }
        return nullptr;
    }
    
    /**
     * @brief Adapt a legacy transport system to modern format
     * @param legacySystem Legacy transport system to adapt
     * @return ModernTransport* Pointer to adapted transport system
     */
    static ModernTransport* adaptLegacyTransport(LegacyTransportSystem* legacySystem) {
        if (legacySystem) {
            return new TransportSystemAdapter(legacySystem);
        }
        return nullptr;
    }

    /**
     * @brief Clean up all legacy transport systems
     */
    static void cleanup() {
        for (auto* system : legacySystems) {
            delete system;
        }
        legacySystems.clear();
    }
};

std::vector<LegacyTransportSystem*> TransportFactory::legacySystems;