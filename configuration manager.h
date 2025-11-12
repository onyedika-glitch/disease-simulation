#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include <map>
#include <string>

class ConfigurationManager {
public:
    // Reads the configuration from the specified file and returns a map of key-value pairs
    std::map<std::string, std::string> readConfig(const std::string& filename);
};

#endif // CONFIGURATION_MANAGER_H