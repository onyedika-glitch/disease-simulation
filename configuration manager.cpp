#include "ConfigurationManager.h"
#include <fstream>
#include <iostream>

std::map<std::string, std::string> ConfigurationManager::readConfig(const std::string& filename) {
    std::ifstream file(filename);
    std::map<std::string, std::string> config;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening configuration file: " << filename << std::endl;
        return config;
    }

    while (std::getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') continue;

        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            config[key] = value;
        }
    }

    file.close();
    return config;
}