/**
 * @file TransportSystemAdapter.h
 * @brief Adapter class to make legacy transport system work with modern interface
 */

#pragma once
#include "ModernTransport.h"
#include "LegacyTransportSystem.h"

/**
 * @class TransportSystemAdapter
 * @brief Adapts a LegacyTransportSystem to work with the ModernTransport interface
 * @inherits ModernTransport
 */
class TransportSystemAdapter : public ModernTransport {
public:
    /**
     * @brief Construct a new Transport System Adapter
     * @param system Pointer to legacy transport system to adapt
     * @note Does not take ownership of the passed system
     */
    TransportSystemAdapter(LegacyTransportSystem* system) : legacySystem(system) {
        if (legacySystem) {
            updateModernAttributes();
        }
    }
    
    /**
     * @brief Destructor
     * @note Does not delete the legacy system as we don't own it
     */
    ~TransportSystemAdapter() {
        // Note: We don't delete legacySystem here as we don't own it
    }

    /**
     * @brief Adapts the legacy transport operation to modern format
     * @return std::string The adapted transport operation message
     * @override
     */
    std::string operationModernTransport() override {
        if (legacySystem) {
            // Adapt the legacy operation to modern format
            std::string legacyOperation = legacySystem->operateOldTransport();
            return "Adapted Transport Operation: " + legacyOperation;
        }
        return "No Legacy System Connected";
    }

    /**
     * @brief Gets the passenger capacity from legacy system
     * @return int The passenger capacity, 0 if no legacy system
     * @override
     */
    int getPassengerCapacity() const override {
        if (legacySystem) {
            return legacySystem->getOldCapacity();
        }
        return 0;
    }

    /**
     * @brief Gets the fuel efficiency from legacy system
     * @return double The fuel efficiency in km per liter
     * @override
     */
    double getFuelEfficiency() const override {
        if (legacySystem) {
            // Convert liters per 100km to km per liter
            float oldUsage = legacySystem->getOldFuelUsage();
            return (oldUsage > 0) ? (100.0 / oldUsage) : 0.0;
        }
        return 0.0;
    }

    /**
     * @brief Gets the transport type from legacy system
     * @return std::string The transport type, "Unknown" if no legacy system
     * @override
     */
    std::string getTransportType() const override {
        if (legacySystem) {
            return std::string("Adapted ") + legacySystem->getVehicleClass();
        }
        return "Unknown";
    }

    /**
     * @brief Gets the maintenance cost from legacy system
     * @return double The maintenance cost, 0.0 if no legacy system
     * @override
     */
    double getMaintenanceCost() const override {
        if (legacySystem) {
            // Convert legacy repair costs to maintenance cost format
            return static_cast<double>(legacySystem->getRepairCosts()) * 1.1; // 10% overhead for adaptation
        }
        return 0.0;
    }

    /**
     * @brief Checks if the legacy system is operational
     * @return bool True if operational, false otherwise
     * @override
     */
    bool isOperational() const override {
        if (legacySystem) {
            return legacySystem->getServiceStatus() == 1;
        }
        return false;
    }

    // Additional adapter-specific methods
    /**
     * @brief Updates the legacy system attributes
     */
    void updateLegacySystem() {
        if (legacySystem) {
            updateModernAttributes();
        }
    }

    /**
     * @brief Checks if a legacy system is connected
     * @return bool True if connected, false otherwise
     */
    bool hasLegacySystem() const {
        return legacySystem != nullptr;
    }
    
private:
    LegacyTransportSystem* legacySystem;  // Non-owning pointer

    /**
     * @brief Updates the modern attributes from the legacy system
     */
    void updateModernAttributes() {
        passengerCapacity = legacySystem->getOldCapacity();
        fuelEfficiency = 100.0 / legacySystem->getOldFuelUsage();
        transportType = std::string("Adapted ") + legacySystem->getVehicleClass();
        maintenanceCost = static_cast<double>(legacySystem->getRepairCosts());
        operational = (legacySystem->getServiceStatus() == 1);
    }
};