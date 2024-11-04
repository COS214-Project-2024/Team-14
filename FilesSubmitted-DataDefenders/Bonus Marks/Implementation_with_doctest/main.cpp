#include <iomanip>
#include <memory>
#include "TaxSystem.h"
#include "TaxStrategy.h"
#include "IncomeTax.h"
#include "BuildingTax.h"
#include "Building.h"
#include "Commercial.h"
#include "Residential.h"
#include "Industrial.h"
#include "ConcreteBuildingFactory.h"
#include "CompositeGovDepartment.h"
#include "HealthDepartment.h"
#include "EducationDepartment.h"
#include "TransportationDepartment.h"
#include <vector>
#include "Student.h"
#include "Worker.h"
#include "Retired.h"
#include "City.h"
#include "District.h"
#include "Neighborhood.h"
#include "SecurityDepartment.h"
#include "Operational.h"
#include "UnderConstruction.h"
#include "Abandoned.h"
#include "SecurityUpgrade.h"
#include "EnergyEfficiencyUpgrade.h"
#include "CapacityUpgrade.h"
#include "CityPlanner.h"
#include "PublicTransitBuilder.h"
#include "RoadNetworkBuilder.h"
#include "UtilityNetworkBuilder.h"
#include "CityResourceDistribution.h"
#include "CityObserver.h"
#include "CitizenSatisfaction.h"
#include "EconomicGrowth.h"
#include "ResourceConsumption.h"
#include "CityStats.h"
#include "ConcreteCityStats.h"
#include "PopulationGrowth.h"
#include "CityStats.h"
#include <cassert>
#include <chrono>
#include "WaterSupply.h"
#include "PowerPlant.h"
#include "WasteManagement.h"
#include "SewageSystem.h"
#include "CityComponent.h"
#include "CityResourceDistribution.h"
#include "ResourceDistributor.h"
#include "LegacyTransportSystem.h"
#include "TransportSystemAdapter.h"
#include "ModernTransport.h"
#include "CitizenPrototype.h"
void testBuildingUpgrades()
{
    ConcreteBuildingFactory factory;
    std::cout << "\n=== Testing Building Upgrades System ===\n";

    // Test Residential Building
    std::cout << "\n--- Testing Residential Building Upgrades ---\n";
    Building *residential = factory.createBuilding("Residential", "Luxury Apartments", 2000, 100, 300000,
                                                   "Residential District", "Uptown");
    std::cout << "\nInitial State:";
    residential->print();

    // Test Security Upgrades to max
    std::cout << "\nTesting Security Upgrades (Should stop at level 5):\n";
    for (int i = 0; i < 6; ++i)
    {
        std::cout << "\nAttempting Security Upgrade " << (i + 1) << ":";
        double prevCost = residential->getCost(); // Move this BEFORE creating upgrade
        SecurityUpgrade security(residential);
        security.applyUpgrade();
        residential->print();
        double costIncrease = residential->getCost() - prevCost;
        std::cout << "Cost Increase: R" << costIncrease << "\n";
    }

    // Test Energy Efficiency Upgrades to max
    std::cout << "\nTesting Energy Efficiency Upgrades (Should stop at level 5):\n";
    for (int i = 0; i < 6; ++i)
    {
        std::cout << "\nAttempting Energy Upgrade " << (i + 1) << ":";
        EnergyEfficiencyUpgrade energy(residential);
        double prevCost = residential->getCost();
        energy.applyUpgrade();
        residential->print();
        double costIncrease = residential->getCost() - prevCost;
        std::cout << "Cost Increase: R" << costIncrease << "\n";
    }

    // Test Capacity Upgrades to max
    std::cout << "\nTesting Capacity Upgrades (Should stop at level 5):\n";
    for (int i = 0; i < 6; ++i)
    {
        std::cout << "\nAttempting Capacity Upgrade " << (i + 1) << ":";
        CapacityUpgrade capacity(residential);
        double prevCost = residential->getCost();
        capacity.applyUpgrade();
        residential->print();
        double costIncrease = residential->getCost() - prevCost;
        std::cout << "Cost Increase: R" << costIncrease << "\n";
    }

    // Test Commercial Building with mixed upgrades
    std::cout << "\n--- Testing Commercial Building Mixed Upgrades ---\n";
    Building *commercial = factory.createBuilding("Commercial", "Shopping Mall", 5000, 200, 500000,
                                                  "Business District", "Downtown");
    std::cout << "\nInitial State:";
    commercial->print();

    // Apply alternating upgrades
    std::cout << "\nApplying mixed upgrades:\n";
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "\nUpgrade Set " << (i + 1) << ":";

        SecurityUpgrade security(commercial);
        double prevCost = commercial->getCost();
        security.applyUpgrade();
        commercial->print();
        std::cout << "Security Upgrade Cost: R" << (commercial->getCost() - prevCost) << "\n";

        EnergyEfficiencyUpgrade energy(commercial);
        prevCost = commercial->getCost();
        energy.applyUpgrade();
        commercial->print();
        std::cout << "Energy Upgrade Cost: R" << (commercial->getCost() - prevCost) << "\n";
    }

    // Test Industrial Building with rapid upgrades
    std::cout << "\n--- Testing Industrial Building Rapid Upgrades ---\n";
    Building *industrial = factory.createBuilding("Industrial", "Factory Complex", 10000, 500, 1000000,
                                                  "Industrial District", "Manufacturing Zone");
    std::cout << "\nInitial State:";
    industrial->print();

    // Max out all upgrades quickly
    std::cout << "\nMaxing out all upgrades:\n";
    for (int i = 0; i < 5; ++i)
    {
        SecurityUpgrade security(industrial);
        EnergyEfficiencyUpgrade energy(industrial);
        CapacityUpgrade capacity(industrial);

        double totalCostBefore = industrial->getCost();
        security.applyUpgrade();
        energy.applyUpgrade();
        capacity.applyUpgrade();
        double totalIncrease = industrial->getCost() - totalCostBefore;

        std::cout << "\nAfter Upgrade Set " << (i + 1) << ":";
        industrial->print();
        std::cout << "Total Cost Increase: R" << totalIncrease << "\n";
    }

    // Try one more upgrade of each type (should fail)
    std::cout << "\nAttempting upgrades beyond max level (should not increase levels):\n";
    SecurityUpgrade security(industrial);
    EnergyEfficiencyUpgrade energy(industrial);
    CapacityUpgrade capacity(industrial);

    double finalCost = industrial->getCost();
    security.applyUpgrade();
    energy.applyUpgrade();
    capacity.applyUpgrade();

    std::cout << "\nFinal State:";
    industrial->print();
    std::cout << "Cost Change After Attempted Upgrades: R"
              << (industrial->getCost() - finalCost)
              << " (Should be 0)\n";

    // Cleanup
    delete residential;
    delete commercial;
    delete industrial;
}

void testBuildingStateSystem()
{
    ConcreteBuildingFactory buildingFactory;
    Building *building = buildingFactory.createBuilding("Residential", "Apartment", 1000, 100, 500000);

    std::cout << "Initial State: " << building->getState() << std::endl;

    building->setState(new UnderConstruction());
    std::cout << "State after setting to Under Construction: " << building->getState() << std::endl;

    building->setState(new Abandoned());
    std::cout << "State after setting to Abandoned: " << building->getState() << std::endl;

    building->setState(new Operational());
    std::cout << "State after setting to Operational: " << building->getState() << std::endl;

    delete building;
}

void testBuildingTaxSystem()
{
    ConcreteBuildingFactory factory;
    std::cout << "\n=== Testing Building Tax System ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    TaxSystem buildingSystem(new BuildingTax());

    // Test individual tax brackets
    double testAmounts[] = {
        500000.0,   // 0.1%  -> 500
        1000000.0,  // 0.2%  -> 2000
        2500000.0,  // 0.3%  -> 7500
        5000000.0,  // 0.5%  -> 25000
        10000000.0, // 11%   -> 1100000
    };

    std::cout << "\nProperty Value (R) | Tax Amount (R) | Tax Rate (%)" << std::endl;
    std::cout << "----------------|---------------|-------------" << std::endl;

    for (double amount : testAmounts)
    {
        double tax = buildingSystem.calculateTax(amount);
        double rate = (tax / amount) * 100;

        std::cout << std::setw(15) << amount << " | "
                  << std::setw(13) << tax << " | "
                  << std::setw(11) << rate << std::endl;
    }

    // Test calculateTotalTax
    std::cout << "\nTesting Total Tax Calculation for Buildings" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    // Create test buildings
    Building *commercial = factory.createBuilding("Commercial", "Mall", 1000.0, 500, 2000000.0);
    Building *residential = factory.createBuilding("Residential", "Apartment", 500.0, 200, 1000000.0);
    Building *industrial = factory.createBuilding("Industrial", "Factory", 2000.0, 100, 5000000.0);

    double expectedTotal =
        buildingSystem.calculateTax(2000000.0) + // Commercial
        buildingSystem.calculateTax(1000000.0) + // Residential
        buildingSystem.calculateTax(5000000.0);  // Industrial

    double actualTotal = industrial->calculateTotalTax();

    std::cout << "Expected total tax: R" << expectedTotal << std::endl;
    std::cout << "Actual total tax: R" << actualTotal << std::endl;
    std::cout << "Test " << (abs(expectedTotal - actualTotal) < 0.01 ? "PASSED" : "FAILED") << std::endl;

    // Cleanup
    delete commercial;
    delete residential;
    delete industrial;
}

void testIncomeTaxSystem()
{
    std::cout << "\n=== Testing Income Tax System ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    TaxSystem incomeSystem(new IncomeTax());

    // Test individual tax brackets
    double testAmounts[] = {
        5000.0,   // 10%  -> 500
        15000.0,  // 11%  -> 1650
        25000.0,  // 12%  -> 3000
        35000.0,  // 14%  -> 4900
        45000.0,  // 15%  -> 6750
        55000.0,  // 16%  -> 8800
        65000.0,  // 17%  -> 11050
        75000.0,  // 18%  -> 13500
        85000.0,  // 19%  -> 16150
        95000.0,  // 20%  -> 19000
        105000.0, // 25%  -> 26250
    };

    std::cout << "\nIncome (R) | Tax Amount (R) | Tax Rate (%)" << std::endl;
    std::cout << "-----------|---------------|-------------" << std::endl;

    for (double amount : testAmounts)
    {
        double tax = incomeSystem.calculateTax(amount);
        double rate = (tax / amount) * 100;

        std::cout << std::setw(10) << amount << " | "
                  << std::setw(13) << tax << " | "
                  << std::setw(11) << rate << std::endl;
    }

    // Test calculateTotalTax
    std::cout << "\nTesting Total Tax Calculation for Citizens" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    // Create test citizens
    CitizenPrototype *studentPrototype = new Student(1, 50000);
    CitizenPrototype *workerPrototype = new Worker(2, 75000);
    CitizenPrototype *retiredPrototype = new Retired(3, 100000);

    double expectedTotal =
        incomeSystem.calculateTax(50000.0) + // Citizen 1
        incomeSystem.calculateTax(75000.0) + // Citizen 2
        incomeSystem.calculateTax(100000.0); // Citizen 3

    double actualTotal = retiredPrototype->calculateTotalTax();

    std::cout << "Expected total tax: R" << expectedTotal << std::endl;
    std::cout << "Actual total tax: R" << actualTotal << std::endl;
    std::cout << "Test " << (abs(expectedTotal - actualTotal) < 0.01 ? "PASSED" : "FAILED") << std::endl;

    // Cleanup
    delete studentPrototype;
    delete workerPrototype;
    delete retiredPrototype;
}

void testIntegratedSystem()
{
    std::cout << "\n=== Testing Integrated System ===" << std::endl;
    ConcreteBuildingFactory buildingFactory;

    // Create buildings
    Building *healthBuilding = buildingFactory.createBuilding("Commercial", "Hospital", 2000, 500, 1000000);
    Building *educationBuilding = buildingFactory.createBuilding("Commercial", "School", 2000, 500, 1000000);
    Building *securityBuilding = buildingFactory.createBuilding("Commercial", "Security", 2000, 500, 1000000);
    Building *transportationBuilding = buildingFactory.createBuilding("Commercial", "Transportation Hub", 2000, 500, 1000000);

    // Create departments
    GovDepartment *healthDept = new HealthDepartment(healthBuilding);
    GovDepartment *educationDept = new EducationDepartment(educationBuilding);
    GovDepartment *securityDept = new SecurityDepartment(securityBuilding);
    GovDepartment *transportationDept = new TransportationDepartment(transportationBuilding);

    // Create composite department
    CompositeGovDepartment compositeDept;
    compositeDept.addDepartment(healthDept);
    compositeDept.addDepartment(educationDept);
    compositeDept.addDepartment(securityDept);
    compositeDept.addDepartment(transportationDept);

    // Create citizens
    CitizenPrototype *student = new Student(1, 50000);
    CitizenPrototype *worker = new Worker(2, 75000);
    CitizenPrototype *retired = new Retired(3, 100000);

    // Calculate total tax from citizens and buildings
    double totalTax = student->calculateTotalTax() + transportationBuilding->calculateTotalTax();
    std::cout << "Total Tax: R" << totalTax << std::endl;

    // Set total Capital for composite department
    compositeDept.setCapital(totalTax);
    compositeDept.distributeCapital();

    // Print building details and corresponding tax allocations
    std::cout << "\nDepartment Buildings and Tax Allocations:" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    std::cout << "\nHealth Department Building:" << std::endl;
    healthBuilding->print();
    std::cout << "Allocated Tax Capital: R" << healthDept->getCapital() << std::endl;

    std::cout << "\nEducation Department Building:" << std::endl;
    educationBuilding->print();
    std::cout << "Allocated Tax Capital: R" << educationDept->getCapital() << std::endl;

    std::cout << "\nSecurity Department Building:" << std::endl;
    securityBuilding->print();
    std::cout << "Allocated Tax Capital: R" << securityDept->getCapital() << std::endl;

    std::cout << "\nTransportation Department Building:" << std::endl;
    transportationBuilding->print();
    std::cout << "Allocated Tax Capital: R" << transportationDept->getCapital() << std::endl;

    // builder test
    std::cout << "\n=== Testing Builder Pattern for Roads ===" << std::endl;

    RoadNetworkBuilder roadBuilder;
    std::cout << "Initial cost estimate: $" << roadBuilder.estimateTotalCost() << "\n";

    // Test validation
    try
    {
        roadBuilder.BuildStructure(); // Should throw - no foundation
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Caught expected error: " << e.what() << "\n";
    }

    // Test complete construction
    roadBuilder.BuildFoundation();
    std::cout << "\nAfter foundation:\n";
    auto *roadPartial = static_cast<RoadNetwork *>(roadBuilder.GetResult());
    roadPartial->displayInfo();
    delete roadPartial;

    // Build complete project
    roadBuilder.reset();
    roadBuilder.BuildFoundation();
    roadBuilder.BuildStructure();
    roadBuilder.BuildFinishing();

    auto *roadResult = static_cast<RoadNetwork *>(roadBuilder.GetResult());
    std::cout << "\nFinal road network:\n";
    roadResult->displayInfo();
    delete roadResult;
    compositeDept.setCapital(totalTax - roadBuilder.estimateTotalCost());
    compositeDept.distributeCapital();

    std::cout << "\n=== Testing Builder Pattern for Transit ===" << std::endl;
    PublicTransitBuilder transitBuilder;
    std::cout << "Initial cost estimate: $" << transitBuilder.estimateTotalCost() << "\n";

    // Test step-by-step construction
    std::cout << "\nTesting step-by-step construction:\n";
    transitBuilder.BuildFoundation();
    auto *transitPartial = static_cast<PublicTransit *>(transitBuilder.GetResult());
    transitPartial->displayInfo();
    delete transitPartial;

    // Test complete construction
    transitBuilder.reset();
    transitBuilder.BuildFoundation();
    transitBuilder.BuildStructure();
    transitBuilder.BuildFinishing();

    std::cout << "\nFinal construction result:\n";
    auto *transitResult = static_cast<PublicTransit *>(transitBuilder.GetResult());
    transitResult->displayInfo();
    delete transitResult;
    compositeDept.setCapital(totalTax - transitBuilder.estimateTotalCost());
    compositeDept.distributeCapital();

    std::cout << "\n=== Testing Builder Pattern for Utility ===" << std::endl;

    UtilityNetworkBuilder utilityBuilder;
    std::cout << "Initial cost estimate: $" << utilityBuilder.estimateTotalCost() << "\n";

    // Test cloning
    utilityBuilder.BuildFoundation();
    utilityBuilder.BuildStructure();
    auto *utilityOriginal = static_cast<UtilityNetwork *>(utilityBuilder.GetResult());
    auto *utilityCloned = utilityOriginal->clone();

    std::cout << "\nComparing original and cloned:\n";
    std::cout << "Original:\n";
    utilityOriginal->displayInfo();
    std::cout << "\nCloned:\n";
    utilityCloned->displayInfo();

    delete utilityOriginal;
    delete utilityCloned;
    compositeDept.setCapital(totalTax - utilityBuilder.estimateTotalCost());
    compositeDept.distributeCapital();
    std::cout << "\nNEW ALLOCATIONS:" << std::endl;
    std::cout << "\nTotal Capital:" << std::endl;
    std::cout << compositeDept.getCapital() << std::endl;

    std::cout << "\nCapital per Dept:" << std::endl;
    std::cout << "\nHealth Department Building:" << std::endl;
    healthBuilding->print();
    std::cout << "Allocated Tax Capital: R" << healthDept->getCapital() << std::endl;

    std::cout << "\nEducation Department Building:" << std::endl;
    educationBuilding->print();
    std::cout << "Allocated Tax Capital: R" << educationDept->getCapital() << std::endl;

    std::cout << "\nSecurity Department Building:" << std::endl;
    securityBuilding->print();
    std::cout << "Allocated Tax Capital: R" << securityDept->getCapital() << std::endl;

    std::cout << "\nTransportation Department Building:" << std::endl;
    transportationBuilding->print();
    std::cout << "Allocated Tax Capital: R" << transportationDept->getCapital() << std::endl;
    // Cleanup
    delete student;
    delete worker;
    delete retired;
    delete healthBuilding;
    delete educationBuilding;
    delete securityBuilding;
    delete transportationBuilding;
    delete healthDept;
    delete educationDept;
    delete securityDept;
    delete transportationDept;
}

void demostratePrototypePattern()
{
    std::cout << "=== Prototype Pattern Demonstration ===" << std::endl;

    // Create prototype instances
    CitizenPrototype *studentPrototype = new Student(1, 0);
    CitizenPrototype *workerPrototype = new Worker(2, 50000);
    CitizenPrototype *retiredPrototype = new Retired(3, 30000);

    // Create clones and modify them
    std::vector<CitizenPrototype *> citizens;

    // Clone and modify students
    CitizenPrototype *student2 = studentPrototype->clone();
    student2->setID(4);
    std::cout << "Attempting to set student salary: (This should not be possible)" << std::endl;
    student2->setSalary(500);
    citizens.push_back(student2);

    CitizenPrototype *student3 = studentPrototype->clone();
    student3->setID(5);
    std::cout << "Student choosing to focus only on studies:" << std::endl;
    student3->setSalary(0);
    citizens.push_back(student3);

    // Clone worker
    CitizenPrototype *worker2 = workerPrototype->clone();
    worker2->setID(6);
    worker2->setSalary(60000);
    citizens.push_back(worker2);

    // Clone retired person
    CitizenPrototype *retired2 = retiredPrototype->clone();
    retired2->setID(7);
    std::cout << "\nAttempting to modify pension (should fail):" << std::endl;
    retired2->setSalary(35000);
    citizens.push_back(retired2);

    // Create a Building
    ConcreteBuildingFactory buildingFactory;
    Building *healthBuilding = buildingFactory.createBuilding("Commercial", "Mall", 2000, 500, 1000000);

    // Associate Citizens with the Building
    std::cout << "\n=== Associating Citizens with a Building ===" << std::endl;
    for (CitizenPrototype *citizen : citizens)
    {
        citizen->setBuilding(healthBuilding);
        std::cout << "Associating " << citizen->getRole() << " #" << citizen->getID() << " with Building" << std::endl;
    }

    // Demonstrate citizen functionality
    std::cout << "\n=== Citizen Information and Tasks ===" << std::endl;
    for (CitizenPrototype *citizen : citizens)
    {
        std::cout << "Role: " << citizen->getRole()
                  << ", ID: " << citizen->getID()
                  << ", " << (citizen->getRole() == "Retired" ? "Pension" : "Salary")
                  << ": R" << citizen->getSalary() << std::endl;
        citizen->performTask();
        std::cout << std::endl;
    }

    // After creating all citizens but before testing stats, add:
    std::cout << "\n=== Debug Citizen Count ===\n";
    std::cout << "Total citizens in vector: " << CitizenPrototype::citizens.size() << "\n";
    std::cout << "Citizen counter value: " << CitizenPrototype::getCitizenCount() << "\n";
    std::cout << "Citizens breakdown:\n";
    for (auto citizen : CitizenPrototype::citizens) {
        std::cout << "ID: " << citizen->getID() << " Role: " << citizen->getRole() << "\n";
    }
    std::cout << "========================\n\n";

    // Cleanup
    for (CitizenPrototype *citizen : citizens)
    {
        delete citizen;
    }

    delete studentPrototype;
    delete workerPrototype;
    delete retiredPrototype;
    delete healthBuilding;

    CitizenPrototype::cleanup();
}

void testCompositePatternNew()
{
    ConcreteBuildingFactory factory;

    try
    {
        std::cout << "\n=== Creating Buildings ===\n";

        // Create multiple buildings in the same neighborhood
        Building *apartment1 = factory.createBuilding(
            "Residential", "Sunset Apartments", 1000.0, 50, 500000.0,
            "Residential District", "Sunset Neighborhood");

        Building *apartment2 = factory.createBuilding(
            "Residential", "Ocean View Apartments", 1200.0, 60, 600000.0,
            "Residential District", "Sunset Neighborhood");

        Building *house = factory.createBuilding(
            "Residential", "Family House", 200.0, 5, 300000.0,
            "Residential District", "Sunset Neighborhood");

        Building *townhouse = factory.createBuilding(
            "Residential", "Modern Townhouse", 150.0, 4, 250000.0,
            "Residential District", "Riverside Neighborhood");

        Building *mall = factory.createBuilding(
            "Commercial", "Central Mall", 5000.0, 200, 2000000.0,
            "Business District", "Shopping Center");

        Building *factory1 = factory.createBuilding(
            "Industrial", "Tech Factory", 10000.0, 500, 5000000.0,
            "Industrial District", "Factory Zone");

        Building *landmark = factory.createBuilding(
            "Landmarks", "City Tower", 2000.0, 1000, 10000000.0,
            "Downtown District", "Central Plaza");

        // Print building details
        apartment1->print();
        apartment2->print();
        house->print();
        townhouse->print();
        mall->print();
        factory1->print();
        landmark->print();

        // Get city instance and print structure
        City *city = City::getInstance();
        std::cout << "\n=== City Structure ===\n";
        city->print();

        // Verification tests
        std::cout << "\n=== Verification Tests ===\n";
        District *residentialDistrict = dynamic_cast<District *>(
            city->findComponent("Residential District"));

        if (residentialDistrict)
        {
            Neighborhood *sunsetNeighborhood = dynamic_cast<Neighborhood *>(
                residentialDistrict->findComponent("Sunset Neighborhood"));
            if (sunsetNeighborhood)
            {
                std::cout << "Sunset Neighborhood building count: "
                          << sunsetNeighborhood->getComponents().size()
                          << " (Expected: 3)\n";
            }
        }

        std::cout << "Total districts: " << city->getComponents().size()
                  << " (Expected: 4)\n";

        // Cleanup
        delete apartment1;
        delete apartment2;
        delete house;
        delete townhouse;
        delete mall;
        delete factory1;
        delete landmark;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        City::cleanup();
        throw;
    }
}

void testObserverPattern() {
    std::cout << "=== Starting City Stats Observer Pattern Test Suite ===\n\n";

    // Helper class to capture console output
    class OutputCapture {
        std::stringstream buffer;
        std::streambuf* oldCout;
    public:
        OutputCapture() : oldCout(std::cout.rdbuf(buffer.rdbuf())) {}
        ~OutputCapture() { std::cout.rdbuf(oldCout); }
        std::string getOutput() { return buffer.str(); }
    };

    // Create the concrete city stats object
    ConcreteCityStats cityStats;

    // Create observers
    CitizenSatisfaction* citizenObs = new CitizenSatisfaction();
    EconomicGrowth* economicObs = new EconomicGrowth();
    PopulationGrowth* populationObs = new PopulationGrowth();

    // Store observers for testing
    std::vector<CityObserver*> observers = {
        citizenObs, economicObs, populationObs
    };

    try {
        // Test 1: Observer Attachment
        std::cout << "\nTest 1: Attaching Observers\n";
        for (auto* obs : observers) {
            cityStats.attach(obs);
            std::cout << "✓ Observer attached successfully\n";
        }

        // Test 2: Basic Stats Update
        std::cout << "\nTest 2: Basic Stats Update\n";
        cityStats.setStats(85.0, 0.05);
        std::cout << "Population: " << cityStats.getPopulation() << "\n";
        std::cout << "Satisfaction: " << cityStats.getSatisfaction() << "\n";
        std::cout << "Growth: " << cityStats.getEconomicGrowth() << "\n";

        // Test 3: Observer Notifications
        std::cout << "\nTest 3: Observer Notifications\n";
        {
            OutputCapture capture;
            cityStats.setStats(87.0, 0.06);
            std::string output = capture.getOutput();
            std::cout << "Notification output captured: " << output.length() << " characters\n";
        }

        // Test 4: Observer Detachment
        std::cout << "\nTest 4: Observer Detachment\n";
        cityStats.detach(populationObs);
        {
            OutputCapture capture;
            cityStats.setStats(88.0, 0.07);
            std::string output = capture.getOutput();
            std::cout << "Reduced notifications captured: " << output.length() << " characters\n";
        }

        // Test 5: Edge Cases
        std::cout << "\nTest 5: Edge Cases\n";
        
        // Zero values
        cityStats.setStats(0.0, 0.0);
        if (cityStats.getPopulation() != 0) {
            std::cerr << "Error: Population should be 0 but was " << cityStats.getPopulation() << std::endl;
            // Optional: throw exception or handle error as needed
        }
                
        // Negative values 
        cityStats.setStats(-20.0, -0.5);
        // Should handle gracefully or clamp
        
        // Large values
        cityStats.setStats(100.0, 1.0);
        if (cityStats.getPopulation() <= 0) {
            std::cerr << "Error: Population must be greater than 0" << std::endl;
            // Optional: throw exception or handle error as needed
        }

        // Test 6: Rapid Updates
        std::cout << "\nTest 6: Rapid Updates\n";
        for(int i = 0; i < 5; i++) {
            cityStats.setStats(
                80.0 + i,
                0.05 + (i * 0.01)
            );
        }

        // Test 7: Null Observer Handling
        std::cout << "\nTest 7: Null Observer Handling\n";
        cityStats.attach(nullptr);  // Should handle gracefully
        cityStats.detach(nullptr);  // Should handle gracefully

        // Test 8: Final Verification
        std::cout << "\nTest 8: Final System State\n";
        cityStats.setStats(90.0, 0.08);
        for(auto* obs : observers) {
            obs->display();
        }

        std::cout << "\n=== Observer Pattern Tests Completed Successfully ===\n";

        // Cleanup
        for(auto* obs : observers) {
            delete obs;
        }

    } catch (const std::exception& e) {
        std::cout << "Error during observer tests: " << e.what() << "\n";
        // Cleanup on exception
        for(auto* obs : observers) {
            delete obs;
        }
        throw;
    }
}

void testMediatorPattern() {
    std::cout << "\n====== COMPREHENSIVE MEDIATOR PATTERN TESTING ======\n";

    // 1. Initialize mediator
    CityResourceDistribution* mediator = CityResourceDistribution::getInstance();
    
    // 2. Create and initialize utilities
    auto* powerPlant = new PowerPlant();
    auto* waterSupply = new WaterSupply();
    auto* wasteManagement = new WasteManagement();
    auto* sewageSystem = new SewageSystem();

    // Initialize resources for utilities
    powerPlant->receiveResources("electricity", 0);  // Initialize with 0
    waterSupply->receiveResources("water", 0);
    wasteManagement->receiveResources("waste", 0);
    sewageSystem->receiveResources("sewage", 0);

    mediator->registerUtility("power", powerPlant);
    mediator->registerUtility("water", waterSupply);
    mediator->registerUtility("waste", wasteManagement);
    mediator->registerUtility("sewage", sewageSystem);

    // 3. Create buildings with explicit resource requirements
    ConcreteBuildingFactory factory;
    
    auto* residential1 = factory.createBuilding("Residential", "Apartment A", 2000, 100, 500000);
    residential1->setResourceRequirement("electricity", 150);
    residential1->setResourceRequirement("water", 100);
    
    auto* residential2 = factory.createBuilding("Residential", "Apartment B", 2000, 100, 500000);
    residential2->setResourceRequirement("electricity", 150);
    residential2->setResourceRequirement("water", 100);
    
    auto* commercial1 = factory.createBuilding("Commercial", "Mall A", 5000, 200, 1000000);
    commercial1->setResourceRequirement("electricity", 300);
    commercial1->setResourceRequirement("water", 200);
    
    auto* commercial2 = factory.createBuilding("Commercial", "Mall B", 5000, 200, 1000000);
    commercial2->setResourceRequirement("electricity", 300);
    commercial2->setResourceRequirement("water", 200);
    
    auto* industrial1 = factory.createBuilding("Industrial", "Factory A", 10000, 500, 2000000);
    industrial1->setResourceRequirement("electricity", 500);
    industrial1->setResourceRequirement("water", 400);

    // Register buildings with mediator
    mediator->registerBuilding(residential1);
    mediator->registerBuilding(residential2);
    mediator->registerBuilding(commercial1);
    mediator->registerBuilding(commercial2);
    mediator->registerBuilding(industrial1);

    // 4. Test initial states
    std::cout << "\n=== Initial Resource States ===\n";
    std::cout << "Residential 1 power requirement: " << residential1->getResourceRequirement("electricity") << "\n";
    std::cout << "Residential 1 water requirement: " << residential1->getResourceRequirement("water") << "\n";

    // 5. Distribute resources
    std::cout << "\n=== Distributing Resources ===\n";
    mediator->distributeResources("power", "electricity", 5000);
    mediator->distributeResources("water", "water", 10000);

    // 6. Verify distribution
    std::cout << "\n=== Resource Levels After Distribution ===\n";
    std::cout << "Residential 1 - Power: " << residential1->getResourceLevel("electricity") 
              << ", Water: " << residential1->getResourceLevel("water") << "\n";
    std::cout << "Commercial 1 - Power: " << commercial1->getResourceLevel("electricity") 
              << ", Water: " << commercial1->getResourceLevel("water") << "\n";

    // 7. Test resource consumption patterns
    std::cout << "\n=== Testing Resource Consumption Patterns ===\n";
    residential1->receiveResource("electricity", 200);
    std::cout << "Adding 200 electricity directly to Residential 1\n";
    std::cout << "New power level: " << residential1->getResourceLevel("electricity") << "\n";
    std::cout << "Still needs power? " << (residential1->needsResource("electricity") ? "Yes" : "No") << "\n";

    // 8. Test edge cases
    std::cout << "\n=== Testing Edge Cases ===\n";
    std::cout << "Testing invalid resource type:\n";
    mediator->distributeResources("power", "invalid_resource", 1000);

    std::cout << "\nTesting negative resource amount:\n";
    mediator->distributeResources("power", "electricity", -100);

    std::cout << "\nTesting zero resource amount:\n";
    mediator->distributeResources("power", "electricity", 0);

    // 9. Test resource depletion
    std::cout << "\n=== Testing Resource Depletion ===\n";
    int totalPowerNeeded = 0;
    for (const auto* building : {residential1, residential2, commercial1, commercial2, industrial1}) {
        if (building->needsResource("electricity")) {
            totalPowerNeeded += building->getResourceRequirement("electricity");
        }
    }
    std::cout << "Total power needed by all buildings: " << totalPowerNeeded << "\n";

    // 10. Test resource distribution fairness
    std::cout << "\n=== Testing Resource Distribution Fairness ===\n";
    mediator->distributeResources("power", "electricity", 1000);
    std::cout << "After distributing 1000 units of power:\n";
    std::cout << "Residential 1: " << residential1->getResourceLevel("electricity") << "\n";
    std::cout << "Commercial 1: " << commercial1->getResourceLevel("electricity") << "\n";
    std::cout << "Industrial 1: " << industrial1->getResourceLevel("electricity") << "\n";

    // 11. Test multiple resource types simultaneously
    std::cout << "\n=== Testing Multiple Resource Types ===\n";
    mediator->distributeResources("power", "electricity", 2000);
    mediator->distributeResources("water", "water", 1500);
    std::cout << "After distributing both power and water:\n";
    std::cout << "Residential 1 - Power: " << residential1->getResourceLevel("electricity") 
            << ", Water: " << residential1->getResourceLevel("water") << "\n";
    std::cout << "Commercial 1 - Power: " << commercial1->getResourceLevel("electricity") 
            << ", Water: " << commercial1->getResourceLevel("water") << "\n";

    // 12. Test resource requirements vs capacity
    std::cout << "\n=== Testing Requirements vs Capacity ===\n";
    for (const auto* building : {residential1, commercial1, industrial1}) {
        std::cout << "Building type: " << building->getBuildingType() << "\n";
        std::cout << "Power requirement: " << building->getResourceRequirement("electricity") << "\n";
        std::cout << "Current power level: " << building->getResourceLevel("electricity") << "\n";
        std::cout << "Water requirement: " << building->getResourceRequirement("water") << "\n";
        std::cout << "Current water level: " << building->getResourceLevel("water") << "\n";
        std::cout << "Needs more power? " << (building->needsResource("electricity") ? "Yes" : "No") << "\n";
        std::cout << "Needs more water? " << (building->needsResource("water") ? "Yes" : "No") << "\n\n";
    }

    // 13. Test utility system capacity
    std::cout << "\n=== Testing Utility System Capacity ===\n";
    mediator->distributeResources("power", "electricity", 100000); // Large amount
    std::cout << "After attempting to distribute large amount of power:\n";
    for (const auto* building : {residential1, commercial1, industrial1}) {
        std::cout << building->getBuildingType() << " power level: " 
                << building->getResourceLevel("electricity") << "\n";
    }

    // 14. System state summary
    std::cout << "\n=== Final System State Summary ===\n";
    std::cout << "Total registered buildings: " << mediator->getBuildingCount() << "\n";
    std::cout << "Total power distributed: " << mediator->getResourceAmount("electricity") << "\n";
    std::cout << "Total water distributed: " << mediator->getResourceAmount("water") << "\n";
    std::cout << "Buildings still needing power: ";
    int powerNeedy = 0;
    for (const auto* building : {residential1, commercial1, industrial1}) {
        if (building->needsResource("electricity")) powerNeedy++;
    }
    std::cout << powerNeedy << "\n";

    // Cleanup
    delete powerPlant;
    delete waterSupply;
    delete wasteManagement;
    delete sewageSystem;
    delete residential1;
    delete residential2;
    delete commercial1;
    delete commercial2;
    delete industrial1;

    CityResourceDistribution::destroyInstance();
}

void testTransportSystemAdaptation() {
    std::cout << "\n====== COMPREHENSIVE TRANSPORT ADAPTER TESTING ======\n";

    // 1. Test basic adapter functionality
    std::cout << "\n=== Basic Adapter Tests ===\n";
    LegacyTransportSystem* legacySystem = new LegacyTransportSystem();
    TransportSystemAdapter* adapter = new TransportSystemAdapter(legacySystem);

    std::cout << "Legacy Operation: " << legacySystem->operateOldTransport() << "\n";
    std::cout << "Adapted Operation: " << adapter->operationModernTransport() << "\n";

    if (adapter->getPassengerCapacity() != legacySystem->getOldCapacity()) {
        std::cerr << "✗ Capacity adaptation test failed\n";
        return;
    }
    std::cout << "✓ Capacity adaptation test passed\n";

    // 2. Test fuel efficiency conversion
    std::cout << "\n=== Fuel Efficiency Conversion Tests ===\n";
    float oldUsage = legacySystem->getOldFuelUsage();
    double newEfficiency = adapter->getFuelEfficiency();
    std::cout << "Old usage (L/100km): " << oldUsage << "\n";
    std::cout << "New efficiency (km/L): " << newEfficiency << "\n";
    if (abs(newEfficiency - (100.0 / oldUsage)) >= 0.001) {
        std::cerr << "✗ Fuel efficiency conversion test failed\n";
        return;
    }
    std::cout << "✓ Fuel efficiency conversion test passed\n";

    // 3. Test maintenance cost adaptation
    std::cout << "\n=== Maintenance Cost Tests ===\n";
    float oldCost = legacySystem->getRepairCosts();
    double newCost = adapter->getMaintenanceCost();
    std::cout << "Old repair costs: $" << oldCost << "\n";
    std::cout << "New maintenance cost: $" << newCost << "\n";
    if (abs(newCost - (oldCost * 1.1)) >= 0.001) {
        std::cerr << "✗ Maintenance cost adaptation test failed\n";
        return;
    }
    std::cout << "✓ Maintenance cost adaptation test passed\n";

    // 4. Test type conversion
    std::cout << "\n=== Transport Type Tests ===\n";
    std::string adaptedType = adapter->getTransportType();
    std::cout << "Original type: " << legacySystem->getVehicleClass() << "\n";
    std::cout << "Adapted type: " << adaptedType << "\n";
    if (adaptedType != "Adapted legacy") {
        std::cerr << "✗ Type conversion test failed\n";
        return;
    }
    std::cout << "✓ Type conversion test passed\n";

    // 5. Test operational status
    std::cout << "\n=== Operational Status Tests ===\n";
    bool isOperational = adapter->isOperational();
    std::cout << "Service status: " << legacySystem->getServiceStatus() << "\n";
    std::cout << "Is operational: " << (isOperational ? "Yes" : "No") << "\n";
    if (isOperational != (legacySystem->getServiceStatus() == 1)) {
        std::cerr << "✗ Operational status test failed\n";
        return;
    }
    std::cout << "✓ Operational status test passed\n";

    // 6. Test factory integration
    std::cout << "\n=== Factory Integration Tests ===\n";
    ModernTransport* modernSystem = TransportFactory::createTransport("modern");
    ModernTransport* adaptedSystem = TransportFactory::createTransport("legacy");

    if (modernSystem == nullptr || adaptedSystem == nullptr) {
        std::cerr << "✗ Factory creation tests failed\n";
        return;
    }
    std::cout << "Modern system type: " << modernSystem->getTransportType() << "\n";
    std::cout << "Adapted system type: " << adaptedSystem->getTransportType() << "\n";
    std::cout << "✓ Factory creation tests passed\n";

    // 7. Test CityPlanner integration
    std::cout << "\n=== CityPlanner Integration Tests ===\n";
    CityPlanner planner;

    ModernTransport* plannerModern = planner.integrateTransportSystem("modern");
    if (plannerModern == nullptr) {
        std::cerr << "✗ Modern transport integration failed\n";
        return;
    }
    std::cout << "✓ Modern transport integration successful\n";

    ModernTransport* plannerLegacy = planner.integrateTransportSystem("legacy");
    if (plannerLegacy == nullptr) {
        std::cerr << "✗ Legacy transport integration failed\n";
        return;
    }
    std::cout << "✓ Legacy transport integration successful\n";

    // Verify transport systems are tracked
    if (planner.getTransportSystems().size() != 2) {
        std::cerr << "✗ Transport system tracking test failed\n";
        return;
    }
    std::cout << "✓ Transport system tracking test passed\n";

    // 8. Test edge cases
    std::cout << "\n=== Edge Case Tests ===\n";

    // Test null legacy system
    try {
        TransportSystemAdapter nullAdapter(nullptr);
        std::cerr << "× Null legacy system test failed\n";
    } catch (const std::exception&) {
        std::cout << "✓ Null legacy system handled correctly\n";
    }

    // Test adapter functionality preservation
    LegacyTransportSystem* newLegacy = new LegacyTransportSystem();
    TransportSystemAdapter* newAdapter = new TransportSystemAdapter(newLegacy);

    for (int i = 0; i < 5; i++) {
        std::string op1 = newAdapter->operationModernTransport();
        std::string op2 = newAdapter->operationModernTransport();
        if (op1 != op2) {
            std::cerr << "✗ Operation consistency test failed\n";
            return;
        }
    }
    std::cout << "✓ Operation consistency test passed\n";

    // 9. Performance test
    std::cout << "\n=== Performance Tests ===\n";
    auto start = std::chrono::high_resolution_clock::now();

    const int ITERATIONS = 10000;
    for (int i = 0; i < ITERATIONS; i++) 
    {
        adapter->getPassengerCapacity();
        adapter->getFuelEfficiency();
        adapter->getMaintenanceCost();
        adapter->isOperational();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Completed " << ITERATIONS << " operations in "
              << duration.count() << " microseconds\n";
    std::cout << "Average time per operation: "
              << (duration.count() / static_cast<double>(ITERATIONS)) << " microseconds\n";

    // Cleanup
    delete adapter;
    delete legacySystem;
    delete modernSystem;
    delete adaptedSystem;
    delete newAdapter;
    delete newLegacy;
    
    TransportFactory::cleanup();

    std::cout << "\n=== Transport Adapter Tests Completed Successfully ===\n";
}

/**
 * @file main.cpp
 * @brief Main entry point for the City Simulation system
 * @author [Your Name]
 * @date 2024
 */

/**
 * @brief Main program entry point
 * @details Runs all system tests and demonstrations:
 * - Building management
 * - Prototype pattern demonstration
 * - Observer pattern tests
 * - Mediator pattern tests
 * - Transport system adaptation tests
 * 
 * @return int 0 on success, 1 on failure
 * @throws std::exception Various exceptions from subsystems
 */

int main()
{
    try
    {
        std::cout << "=== Starting City Simulation System ===\n";
        testCompositePatternNew();

        std::cout << "\n=== Testing Building State System ===\n";

        // Test Building Upgrades System
        testBuildingUpgrades();
        std::cout << "\n=== Testing Building Upgrades System ===\n";

        // Test Building Tax System brackets
        testBuildingTaxSystem();
        std::cout << "\n=== Testing BuidlingTax System ===\n";

        // Test Income Tax System brackets
        testIncomeTaxSystem();
        std::cout << "\n=== Testing IncomeTax System ===\n";

        // Test Integrated System
        testIntegratedSystem();
        std::cout << "\n=== Testing Integrated System ===\n";

        Building::cleanup();  // Clean up the static vector
        CityResourceDistribution::getInstance()->cleanup();

        demostratePrototypePattern();
        std::cout << "\n=== Testing Prototype System ===\n";

        testObserverPattern();
        std::cout << "\n=== Testing Observer System ===\n";
        // Cleanup the singleton at the end

        Building::cleanup();
        CityResourceDistribution::getInstance()->cleanup();

        testMediatorPattern();
        std::cout << "\n=== Testing Mediator System ===\n";

        testTransportSystemAdaptation();
        std::cout << "\n=== Testing Transport System Adaptation ===\n";

        City::cleanup();
        Building::cleanup();  // Clean up the static vector
        CityResourceDistribution::destroyInstance();

        std::cout << "\nProgram completed successfully!\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error occurred in main: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nAll tests completed.\n"
              << std::endl;
    return 0;
}