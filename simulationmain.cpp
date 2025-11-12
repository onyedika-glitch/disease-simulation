#include <iostream>
#include <vector>
#include "ConfigurationManager.h"
#include "SimulationConfig.h"
#include "Simulation.h"

int main() {
    // Step 3: Read Configuration
    ConfigurationManager configManager;
    auto configMap = configManager.readConfig("disease_in.ini");

    // Step 4: Load Configuration into SimulationConfig
    SimulationConfig simConfig;
    simConfig.loadFromMap(configMap);

    // Step 5: Initialize Populations
    std::vector<Population> populations;
    int numberOfPopulations = 2; // Example: you can adjust this based on your needs
    for (int i = 0; i < numberOfPopulations; ++i) {
        Population population;
        initializePopulation(population, simConfig);
        populations.push_back(population);
    }

    // Step 6: Run the Simulation
    runSimulation(populations, simConfig);

    return 0;
}