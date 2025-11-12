#ifndef SIMULATION_CONFIG_H
#define SIMULATION_CONFIG_H

#include <map>
#include <string>

class SimulationConfig {
public:
    int populationSize;
    double vaccinationRate;
    int initialInfectious;
    int contactRate;
    int interPopulationContacts;

    // Loads configuration parameters from a map of key-value pairs
    void loadFromMap(const std::map<std::string, std::string>& configMap);
};

#endif // SIMULATION_CONFIG_H