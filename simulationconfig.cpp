#include "SimulationConfig.h"
#include <iostream>

void SimulationConfig::loadFromMap(const std::map<std::string, std::string>& configMap) {
    try {
        if (configMap.find("populationSize") != configMap.end()) {
            populationSize = std::stoi(configMap.at("populationSize"));
        }
        if (configMap.find("vaccinationRate") != configMap.end()) {
            vaccinationRate = std::stod(configMap.at("vaccinationRate"));
        }
        if (configMap.find("initialInfectious") != configMap.end()) {
            initialInfectious = std::stoi(configMap.at("initialInfectious"));
        }
        if (configMap.find("contactRate") != configMap.end()) {
            contactRate = std::stoi(configMap.at("contactRate"));
        }
        if (configMap.find("interPopulationContacts") != configMap.end()) {
            interPopulationContacts = std::stoi(configMap.at("interPopulationContacts"));
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading configuration: " << e.what() << std::endl;
    }
}