#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iomanip>
#include <memory>
#include <array>
#include <string>
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
#include "doctest.h"
const double EPSILON = 1e-5;

TEST_CASE("Testing Residential Building Upgrades") 
{
    ConcreteBuildingFactory factory;
    Building* residential = factory.createBuilding("Residential", "Luxury Apartments", 2000, 100, 300000, "Residential District", "Uptown");

    SUBCASE("Initial State") 
    {
        CHECK(residential->getCost() == 300000); 
    }

    SUBCASE("Security Upgrades to Max Level") 
    {
        for (int i = 0; i < 6; ++i) 
        {
            long double prevCost = residential->getCost();
            SecurityUpgrade security(residential);
            security.applyUpgrade();
            long double costIncrease = residential->getCost() - prevCost;
            if (i < 4) {
                CHECK(costIncrease > doctest::Approx(0.0).epsilon(1e-9));
            } else {
                CHECK(costIncrease == doctest::Approx(0.0).epsilon(1e-9)); // Ensure no change in cost beyond max level
            }
        }
    }

    SUBCASE("Energy Efficiency Upgrades to Max Level") 
    {
        for (int i = 0; i < 5; ++i) {
            double prevCost = residential->getCost();
            EnergyEfficiencyUpgrade energy(residential);
            energy.applyUpgrade();
            double costIncrease = residential->getCost() - prevCost;
            if (i < 4) {
                CHECK(costIncrease > doctest::Approx(0.0).epsilon(1e-9));
            } else {
                CHECK(costIncrease == doctest::Approx(0.0).epsilon(1e-9)); // Ensure no change in cost beyond max level
            }
        }
    }

    SUBCASE("Capacity Upgrades to Max Level") 
    {
        for (int i = 0; i < 5; ++i) {
            double prevCost = residential->getCost();
            CapacityUpgrade capacity(residential);
            capacity.applyUpgrade();
            double costIncrease = residential->getCost() - prevCost;
            if (i < 4) {
                CHECK(costIncrease > doctest::Approx(0.0).epsilon(1e-9));
            } else {
                CHECK(costIncrease == doctest::Approx(0.0).epsilon(1e-9)); // Ensure no change in cost beyond max level
            }
        }
    }

    delete residential;
}

TEST_CASE("Testing Commercial Building Mixed Upgrades") 
{
    ConcreteBuildingFactory factory;
    Building* commercial = factory.createBuilding("Commercial", "Shopping Mall", 5000, 200, 500000, "Business District", "Downtown");

    SUBCASE("Initial State") 
    {
        CHECK(commercial->getCost() == 500000); 
    }

    SUBCASE("Applying Mixed Upgrades") 
    {
        for (int i = 0; i < 3; ++i) {
            double prevCost = commercial->getCost();

            SecurityUpgrade security(commercial);
            security.applyUpgrade();
            CHECK(commercial->getCost() > prevCost);
            prevCost = commercial->getCost();

            EnergyEfficiencyUpgrade energy(commercial);
            energy.applyUpgrade();
            CHECK(commercial->getCost() > prevCost);
            prevCost = commercial->getCost();
        }
    }

    delete commercial;
}

TEST_CASE("Testing Industrial Building Rapid Upgrades") 
{
    ConcreteBuildingFactory factory;
    Building* industrial = factory.createBuilding("Industrial", "Factory Complex", 10000, 500, 1000000, "Industrial District", "Manufacturing Zone");

    SecurityUpgrade security(industrial);
    EnergyEfficiencyUpgrade energy(industrial);
    CapacityUpgrade capacity(industrial);

    SUBCASE("Initial State") 
    {
        CHECK(industrial->getCost() == doctest::Approx(1000000.0).epsilon(1e-9)); 
    }

    SUBCASE("Maxing Out All Upgrades") 
    {   
        while(!(industrial->getEnergyLevel()==5 && industrial->getCapacityLevel()==5 && industrial->getEnergyLevel()==5))
        {   long double totalCostBefore = industrial->getCost();
            industrial->upgradeSecurity();
            industrial->upgradeEnergyEfficiency();
            industrial->upgradeCapacity();
            long double totalIncrease = industrial->getCost() - totalCostBefore;
            CHECK(totalIncrease > doctest::Approx(0.0).epsilon(1e-9));
        }        
    }

    SUBCASE("Attempting Upgrades Beyond Max Level") 
    {   
        //max out each
        while(!(industrial->getEnergyLevel()==5 && industrial->getCapacityLevel()==5 && industrial->getEnergyLevel()==5))
        {   
            industrial->upgradeSecurity();
            industrial->upgradeEnergyEfficiency();
            industrial->upgradeCapacity();
        }  
        double finalCost = industrial->getCost();
        std::cout << std::fixed << std::setprecision(2); 
        std::cout << "Initial finalCost before additional upgrades: " << finalCost << std::endl;

        // Attempt to apply upgrades again
        industrial->upgradeSecurity();
        std::cout << "Cost after security upgrade: " << industrial->getCost() << std::endl;
        industrial->upgradeEnergyEfficiency();
        std::cout << "Cost after energy upgrade: " << industrial->getCost() << std::endl;
        industrial->upgradeCapacity();
        std::cout << "Cost after capacity upgrade: " << industrial->getCost() << std::endl;

        CHECK(industrial->getCost() == doctest::Approx(finalCost).epsilon(1e-9));
    }
    delete industrial;
}

TEST_CASE("Testing Building State Transitions")
{
    ConcreteBuildingFactory buildingFactory;
    Building* building = buildingFactory.createBuilding("Residential", "Apartment", 1000, 100, 500000);

    building->setState(new Operational());
    std::string initialState = building->getState();

    building->setState(new UnderConstruction());
    std::string underConstructionState = building->getState();

    building->setState(new Abandoned());
    std::string abandonedState = building->getState();

    CHECK(initialState == "Operational"); 
    CHECK(underConstructionState == "Under Construction"); 
    CHECK(abandonedState == "Abandoned"); 

    delete building; 
}

TEST_CASE("Testing Income Tax System") 
{
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

    for (double amount : testAmounts) 
    {
        double tax = incomeSystem.calculateTax(amount);
        double rate = (tax / amount) * 100;

        if (amount <= 5000) {
            CHECK(tax == doctest::Approx(500).epsilon(0.01));
        } else if (amount <= 15000) {
            CHECK(tax == doctest::Approx(1650).epsilon(0.01));
        } else if (amount <= 25000) {
            CHECK(tax == doctest::Approx(3000).epsilon(0.01));
        } else if (amount <= 35000) {
            CHECK(tax == doctest::Approx(4900).epsilon(0.01));
        } else if (amount <= 45000) {
            CHECK(tax == doctest::Approx(6750).epsilon(0.01));
        } else if (amount <= 55000) {
            CHECK(tax == doctest::Approx(8800).epsilon(0.01));
        } else if (amount <= 65000) {
            CHECK(tax == doctest::Approx(11050).epsilon(0.01));
        } else if (amount <= 75000) {
            CHECK(tax == doctest::Approx(13500).epsilon(0.01));
        } else if (amount <= 85000) {
            CHECK(tax == doctest::Approx(16150).epsilon(0.01));
        } else if (amount <= 95000) {
            CHECK(tax == doctest::Approx(19000).epsilon(0.01));
        } else {
            CHECK(tax == doctest::Approx(26250).epsilon(0.01));
        }
    }

    CitizenPrototype *studentPrototype = new Student(1, 50000);
    CitizenPrototype *workerPrototype = new Worker(2, 75000);
    CitizenPrototype *retiredPrototype = new Retired(3, 100000);

    double expectedTotal =
        incomeSystem.calculateTax(50000.0) + 
        incomeSystem.calculateTax(75000.0) + 
        incomeSystem.calculateTax(100000.0); 

    double actualTotal = retiredPrototype->calculateTotalTax();

    std::cout << "Expected total tax: R" << expectedTotal << std::endl;
    std::cout << "Actual total tax: R" << actualTotal << std::endl;

    CHECK(actualTotal == doctest::Approx(expectedTotal).epsilon(0.01)); 

    delete studentPrototype;
    delete workerPrototype;
    delete retiredPrototype;
}

TEST_CASE("Demonstrate Prototype Pattern") 
{

    CitizenPrototype *studentPrototype = new Student(1, 0);
    CitizenPrototype *workerPrototype = new Worker(2, 50000);
    CitizenPrototype *retiredPrototype = new Retired(3, 30000);
    std::vector<CitizenPrototype *> citizens;

    CitizenPrototype *student2 = studentPrototype->clone();
    student2->setID(4);
    student2->setSalary(500);
    citizens.push_back(student2);

    CitizenPrototype *student3 = studentPrototype->clone();
    student3->setID(5);
    student3->setSalary(0); 
    citizens.push_back(student3);

    CitizenPrototype *worker2 = workerPrototype->clone();
    worker2->setID(6);
    worker2->setSalary(60000);
    citizens.push_back(worker2);

    CitizenPrototype *retired2 = retiredPrototype->clone();
    retired2->setID(7);
    retired2->setSalary(35000);
    CHECK(retired2->getSalary()!=35000); 
    citizens.push_back(retired2);

    ConcreteBuildingFactory buildingFactory;
    Building *healthBuilding = buildingFactory.createBuilding("Commercial", "Mall", 2000, 500, 1000000);

    // Associate Citizens with the Building
    std::vector<std::string> arr = { "Associating Student #4 with Building",
                                    "Associating Student #5 with Building" ,
                                    "Associating Worker #6 with Building",
                                    "Associating Retired #7 with Building" };
    std::string ss="";
    int c=0;
    for (CitizenPrototype *citizen : citizens) {
        citizen->setBuilding(healthBuilding);
        int id = citizen->getID();
        ss= "Associating " + citizen->getRole() + " #" + std::to_string(id) + " with Building";
        CHECK(ss==arr[c]);
        c++;
        ss="";
    }

    arr = { "Role: Student, ID: 4, Salary: R500.00",
                                    "Role: Student, ID: 5, Salary: R0.00" ,
                                    "Role: Worker, ID: 6, Salary: R60000.00",
                                    "Role: Retired, ID: 7, Pension: R30000.00"};
    ss="";
    c=0;
    std::cout << "\n=== Citizen Information and Tasks ===" << std::endl;
    for (CitizenPrototype *citizen : citizens) 
    {   
        int id = citizen->getID();
        double salary=citizen->getSalary();
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << salary; 
        std::string formattedSalary = oss.str();
        ss="Role: "+citizen->getRole()+", ID: "+std::to_string(id)+", "+(citizen->getRole() == "Retired" ? "Pension" : "Salary")+": R" 
        +formattedSalary;
        CHECK(ss==arr[c]);
        c++;
        ss="";
    }

    // Cleanup
    for (CitizenPrototype *citizen : citizens) {
        delete citizen;
    }

    delete studentPrototype;
    delete workerPrototype;
    delete retiredPrototype;
    delete healthBuilding;

    CitizenPrototype::cleanup();
}

TEST_CASE("Composite Pattern Test")
{
   ConcreteBuildingFactory factory;
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


    City *city = City::getInstance();



    // Verification tests
    std::cout << "\n=== Verification Tests ===\n";
    District *residentialDistrict = dynamic_cast<District *>(
        city->findComponent("Residential District"));

    District *defaultdistrict = dynamic_cast<District *>(
        city->findComponent("Default District"));

    city->remove(defaultdistrict);
    CHECK(city->findComponent("Default District")==nullptr);
    if (residentialDistrict)
    {
        Neighborhood *sunsetNeighborhood = dynamic_cast<Neighborhood *>(
            residentialDistrict->findComponent("Sunset Neighborhood"));

        CHECK(sunsetNeighborhood != nullptr);
        CHECK(sunsetNeighborhood->getComponents().size() == 3);
    }

    CHECK(city->getComponents().size() == 4);

        delete apartment1;
        delete apartment2;
        delete house;
        delete townhouse;
        delete mall;
        delete factory1;
        delete landmark;
    

}

TEST_CASE("Observer Pattern Test Suite") 
{

    class OutputCapture 
    {
        std::stringstream buffer;
        std::streambuf* oldCout;
    public:
        OutputCapture() : oldCout(std::cout.rdbuf(buffer.rdbuf())) {}
        ~OutputCapture() { std::cout.rdbuf(oldCout); }
        std::string getOutput() { return buffer.str(); }
    };

    ConcreteCityStats cityStats;

    CitizenSatisfaction* citizenObs = new CitizenSatisfaction();
    EconomicGrowth* economicObs = new EconomicGrowth();
    PopulationGrowth* populationObs = new PopulationGrowth();


    std::vector<CityObserver*> observers = 
    {
        citizenObs, economicObs, populationObs
    };


    SUBCASE("Observer Attachment") 
    {
        for (auto* obs : observers) {
            cityStats.attach(obs);
            CHECK(true); 
        }
    }

    SUBCASE("Basic Stats Update") 
    {
        cityStats.setStats(85.0, 0.05);
        CHECK(cityStats.getSatisfaction() == 85.0);
        CHECK(cityStats.getEconomicGrowth() == 0.05);
    }

    // Test 3: Observer Notifications
    SUBCASE("Observer Notifications") {
        OutputCapture capture;
        cityStats.setStats(87.0, 0.06);
        std::string output = capture.getOutput();
        CHECK(output.length() > 0); // Expect some output to be generated
    }

    // // Test 4: Observer Detachment
    // SUBCASE("Observer Detachment") 
    // {   

    //     std::cout << "\nTest 4: Observer Detachment\n";

    //     cityStats.detach(populationObs);
        
    //         OutputCapture capture;
    //         cityStats.setStats(88.0, 0.07);
    //         std::string output = capture.getOutput();
    //         std::cout << "Reduced notifications captured: " << output.length() << " characters\n";
        
    //     CHECK(true); // Assuming this is less than with observer attached
    
    // }

    // Test 5: Edge Cases
    SUBCASE("Edge Cases") {
        // Zero values
        cityStats.setStats(0.0, 0.0);
        CHECK(cityStats.getPopulation() == 0);

        // Negative values (assuming it should handle gracefully or clamp)
        cityStats.setStats(-20.0, -0.5);
        CHECK(cityStats.getPopulation() >= 0); // Assuming it does not go negative
        
        CitizenPrototype* newCitizen=new Worker(4,4);
        // Large values
        cityStats.setStats(100.0, 1.0);
        CHECK(cityStats.getPopulation() > 0);
        delete newCitizen;
    }



    // Test 7: Null Observer Handling
    SUBCASE("Null Observer Handling") {
        cityStats.attach(nullptr);  // Should handle gracefully
        cityStats.detach(nullptr);  // Should handle gracefully
        CHECK(true); // If we reach here, it handled gracefully
    }

    // Test 8: Final Verification
    SUBCASE("Final System State") {
        cityStats.setStats(90.0, 0.08);
        for(auto* obs : observers) {
            obs->display();
            CHECK(true); // If we reach here, display succeeded
        }
    }

    for(auto* obs : observers) {
        delete obs;
    }
}

TEST_CASE("Mediator Pattern Test Suite") 
{
    CityResourceDistribution* mediator = CityResourceDistribution::getInstance();

    auto* powerPlant = new PowerPlant();
    auto* waterSupply = new WaterSupply();
    auto* wasteManagement = new WasteManagement();
    auto* sewageSystem = new SewageSystem();

    powerPlant->receiveResources("electricity", 0);
    waterSupply->receiveResources("water", 0);
    wasteManagement->receiveResources("waste", 0);
    sewageSystem->receiveResources("sewage", 0);

    mediator->registerUtility("power", powerPlant);
    mediator->registerUtility("water", waterSupply);
    mediator->registerUtility("waste", wasteManagement);
    mediator->registerUtility("sewage", sewageSystem);

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

    mediator->registerBuilding(residential1);
    mediator->registerBuilding(residential2);
    mediator->registerBuilding(commercial1);
    mediator->registerBuilding(commercial2);
    mediator->registerBuilding(industrial1);

    CHECK(residential1->getResourceRequirement("electricity") == 150);
    CHECK(residential1->getResourceRequirement("water") == 100);

    mediator->distributeResources("electricity", "electricity", 5000);

}

TEST_CASE("Comprehensive Transport Adapter Testing") {

    LegacyTransportSystem* legacySystem = new LegacyTransportSystem();
    TransportSystemAdapter* adapter = new TransportSystemAdapter(legacySystem);

    CHECK(legacySystem->operateOldTransport() == "Operating Legacy Transport: legacy");
    CHECK(adapter->operationModernTransport() == "Adapted Transport Operation: Operating Legacy Transport: legacy");
    CHECK(adapter->getPassengerCapacity() == legacySystem->getOldCapacity());
    float oldUsage = legacySystem->getOldFuelUsage();
    double newEfficiency = adapter->getFuelEfficiency();
    CHECK(abs(newEfficiency - (100.0 / oldUsage)) < 0.001);

    float oldCost = legacySystem->getRepairCosts();
    double newCost = adapter->getMaintenanceCost();
    CHECK(abs(newCost - (oldCost * 1.1)) < 0.001);

    std::string adaptedType = adapter->getTransportType();
    CHECK(adaptedType == "Adapted legacy");

    bool isOperational = adapter->isOperational();
    CHECK(isOperational == (legacySystem->getServiceStatus() == 1));

    ModernTransport* modernSystem = TransportFactory::createTransport("modern");
    ModernTransport* adaptedSystem = TransportFactory::createTransport("legacy");
    CHECK(modernSystem != nullptr);
    CHECK(adaptedSystem != nullptr);

    CityPlanner planner;
    ModernTransport* plannerModern = planner.integrateTransportSystem("modern");
    CHECK(plannerModern != nullptr);

    ModernTransport* plannerLegacy = planner.integrateTransportSystem("legacy");
    CHECK(plannerLegacy != nullptr);
    CHECK(planner.getTransportSystems().size() == 2);


    TransportSystemAdapter* nulltest=new TransportSystemAdapter(nullptr);
    CHECK(true); //no segfault

    const int ITERATIONS = 10000;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < ITERATIONS; i++) {
        adapter->getPassengerCapacity();
        adapter->getFuelEfficiency();
        adapter->getMaintenanceCost();
        adapter->isOperational();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    double averageTime = duration.count() / static_cast<double>(ITERATIONS);
    CHECK(averageTime >= 0); 


    delete adapter;
    delete legacySystem;
    delete modernSystem;
    delete adaptedSystem;

    TransportFactory::cleanup();
}
