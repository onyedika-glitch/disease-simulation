#include "ConfigurationManager.h"
#include "SimulationConfig.h"
#include <iostream>

int main() {
    ConfigurationManager configManager;
    auto configMap = configManager.readConfig("disease_in.ini");

    SimulationConfig simConfig;
    simConfig.loadFromMap(configMap);

    // Example of accessing configuration values
    std::cout << "Population Size: " << simConfig.populationSize << std::endl;
    std::cout << "Vaccination Rate: " << simConfig.vaccinationRate << std::endl;

    // Continue with the rest of your simulation setup...

    return 0;
}