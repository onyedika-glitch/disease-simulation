#include "ConfigurationManager.h"
#include <iostream>

int main() {
    ConfigurationManager configManager;
    auto configMap = configManager.readConfig("disease_in.ini");

    // Example of accessing configuration values
    if (configMap.find("populationSize") != configMap.end()) {
        int populationSize = std::stoi(configMap.at("populationSize"));
        std::cout << "Population Size: " << populationSize << std::endl;
    }

    // Continue with the rest of your simulation setup...

    return 0;
}