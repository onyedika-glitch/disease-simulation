#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>
#include "SimulationConfig.h"

enum class HealthStatus { Susceptible, Infectious, Vaccinated, Recovered };

struct Person {
    HealthStatus status;
};

struct Population {
    std::vector<Person> people;
};

// Function declarations
void initializePopulation(Population& population, const SimulationConfig& config);
void simulateDay(Population& population);
void interPopulationContact(Population& pop1, Population& pop2);
void runSimulation(std::vector<Population>& populations, const SimulationConfig& config);
void writeSummaryStatistics(const std::string& filename, int timesteps, int vaccinated, int recovered, int susceptible);
void writeSimulationDetails(const std::string& filename, int timestep, const Population& population);
void printSummary(int timesteps, int vaccinated, int recovered, int susceptible);

#endif // SIMULATION_H