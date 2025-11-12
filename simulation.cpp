#include "Simulation.h"
#include <fstream>
#include <iostream>
#include <random>

void initializePopulation(Population& population, const SimulationConfig& config) {
    population.people.resize(config.populationSize);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (auto& person : population.people) {
        if (dis(gen) < config.vaccinationRate) {
            person.status = HealthStatus::Vaccinated;
        }
        else {
            person.status = HealthStatus::Susceptible;
        }
    }

    // Start with initial infectious persons
    for (int i = 0; i < config.initialInfectious; ++i) {
        population.people[i].status = HealthStatus::Infectious;
    }
}

void simulateDay(Population& population) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, population.people.size() - 1);

    for (auto& person : population.people) {
        if (person.status == HealthStatus::Infectious) {
            for (int i = 0; i < 6; ++i) {
                int contactIndex = dis(gen);
                if (population.people[contactIndex].status == HealthStatus::Susceptible) {
                    population.people[contactIndex].status = HealthStatus::Infectious;
                }
            }
        }
    }
}

void interPopulationContact(Population& pop1, Population& pop2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis1(0, pop1.people.size() - 1);
    std::uniform_int_distribution<> dis2(0, pop2.people.size() - 1);

    for (int i = 0; i < 5; ++i) {
        int index1 = dis1(gen);
        int index2 = dis2(gen);

        if (pop1.people[index1].status == HealthStatus::Infectious &&
            pop2.people[index2].status == HealthStatus::Susceptible) {
            pop2.people[index2].status = HealthStatus::Infectious;
        }

        if (pop2.people[index2].status == HealthStatus::Infectious &&
            pop1.people[index1].status == HealthStatus::Susceptible) {
            pop1.people[index1].status = HealthStatus::Infectious;
        }
    }
}

void runSimulation(std::vector<Population>& populations, const SimulationConfig& config) {
    int timestep = 0;
    bool diseaseActive = true;

    while (diseaseActive) {
        diseaseActive = false;
        for (auto& population : populations) {
            simulateDay(population);
            for (const auto& person : population.people) {
                if (person.status == HealthStatus::Infectious) {
                    diseaseActive = true;
                    break;
                }
            }
        }

        // Randomly select two populations for inter-population contact
        if (populations.size() > 1) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, populations.size() - 1);
            int popIndex1 = dis(gen);
            int popIndex2 = dis(gen);
            while (popIndex1 == popIndex2) {
                popIndex2 = dis(gen);
            }
            interPopulationContact(populations[popIndex1], populations[popIndex2]);
        }

        // Write simulation details for each timestep
        for (size_t i = 0; i < populations.size(); ++i) {
            writeSimulationDetails("disease_details.csv", timestep, populations[i]);
        }

        timestep++;
    }

    // Calculate summary statistics
    int vaccinated = 0, recovered = 0, susceptible = 0;
    for (const auto& population : populations) {
        for (const auto& person : population.people) {
            switch (person.status) {
            case HealthStatus::Vaccinated: vaccinated++; break;
            case HealthStatus::Recovered: recovered++; break;
            case HealthStatus::Susceptible: susceptible++; break;
            default: break;
            }
        }
    }

    // Write summary statistics
    writeSummaryStatistics("disease_stats.csv", timestep, vaccinated, recovered, susceptible);

    // Print summary
    printSummary(timestep, vaccinated, recovered, susceptible);
}

void writeSummaryStatistics(const std::string& filename, int timesteps, int vaccinated, int recovered, int susceptible) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    file << "Timesteps,Vaccinated,Recovered,Susceptible\n";
    file << timesteps << "," << vaccinated << "," << recovered << "," << susceptible << "\n";

    file.close();
}

void writeSimulationDetails(const std::string& filename, int timestep, const Population& population) {
    std::ofstream file(filename, std::ios_base::app); // Append mode

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    int susceptible = 0, infectious = 0, vaccinated = 0, recovered = 0;
    for (const auto& person : population.people) {
        switch (person.status) {
        case HealthStatus::Susceptible: susceptible++; break;
        case HealthStatus::Infectious: infectious++; break;
        case HealthStatus::Vaccinated: vaccinated++; break;
        case HealthStatus::Recovered: recovered++; break;
        }
    }

    file << timestep << "," << susceptible << "," << infectious << "," << vaccinated << "," << recovered << "\n";
    file.close();
}

void printSummary(int timesteps, int vaccinated, int recovered, int susceptible) {
    std::cout << "Simulation completed in " << timesteps << " timesteps.\n";
    std::cout << "Vaccinated: " << vaccinated << "\n";
    std::cout << "Recovered: " << recovered << "\n";
    std::cout << "Susceptible: " << susceptible << "\n";
}

#include "Simulation.h"
#include <fstream>
#include <iostream>
#include <random>

// Existing functions...

void runSimulation(std::vector<Population>& populations, const SimulationConfig& config) {
    int timestep = 0;
    bool diseaseActive = true;

    while (diseaseActive) {
        diseaseActive = false;
        for (auto& population : populations) {
            simulateDay(population);
            for (const auto& person : population.people) {
                if (person.status == HealthStatus::Infectious) {
                    diseaseActive = true;
                    break;
                }
            }
        }

        // Randomly select two populations for inter-population contact
        if (populations.size() > 1) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, populations.size() - 1);
            int popIndex1 = dis(gen);
            int popIndex2 = dis(gen);
            while (popIndex1 == popIndex2) {
                popIndex2 = dis(gen);
            }
            interPopulationContact(populations[popIndex1], populations[popIndex2]);
        }

        timestep++;
    }

    // Calculate summary statistics
    int vaccinated = 0, recovered = 0, susceptible = 0;
    for (const auto& population : populations) {
        for (const auto& person : population.people) {
            switch (person.status) {
            case HealthStatus::Vaccinated: vaccinated++; break;
            case HealthStatus::Recovered: recovered++; break;
            case HealthStatus::Susceptible: susceptible++; break;
            default: break;
            }
        }
    }

    // Write summary statistics
    writeSummaryStatistics("disease_stats.csv", timestep, vaccinated, recovered, susceptible);

    // Print summary
    printSummary(timestep, vaccinated, recovered, susceptible);
}

// Function to write summary statistics to a CSV file
void writeSummaryStatistics(const std::string& filename, int timesteps, int vaccinated, int recovered, int susceptible) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // Write the header
    file << "Timesteps,Vaccinated,Recovered,Susceptible\n";

    // Write the data
    file << timesteps << "," << vaccinated << "," << recovered << "," << susceptible << "\n";

    file.close();
}

// Other existing functions...

#include <fstream>
#include <iostream>
#include <string>
#include "Simulation.h"

// Function to write simulation details to a CSV file
void writeSimulationDetails(const std::string& filename, int timestep, const std::vector<Population>& populations) {
    std::ofstream file(filename, std::ios_base::app); // Append mode

    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }

    // Write the header if it's the first timestep
    if (timestep == 0) {
        file << "Timestep,Population, Susceptible, Infectious, Vaccinated, Recovered\n";
    }

    // Write details for each population
    for (size_t i = 0; i < populations.size(); ++i) {
        int susceptible = 0, infectious = 0, vaccinated = 0, recovered = 0;
        for (const auto& person : populations[i].people) {
            switch (person.status) {
            case HealthStatus::Susceptible: susceptible++; break;
            case HealthStatus::Infectious: infectious++; break;
            case HealthStatus::Vaccinated: vaccinated++; break;
            case HealthStatus::Recovered: recovered++; break;
            }
        }

        file << timestep << "," << i << "," << susceptible << "," << infectious << "," << vaccinated << "," << recovered << "\n";
    }

    file.close();
}

void runSimulation(std::vector<Population>& populations, const SimulationConfig& config) {
    int timestep = 0;
    bool diseaseActive = true;

    // Clear the file before starting the simulation
    std::ofstream file("disease_details.csv");
    file.close();

    while (diseaseActive) {
        diseaseActive = false;
        for (auto& population : populations) {
            simulateDay(population);
            for (const auto& person : population.people) {
                if (person.status == HealthStatus::Infectious) {
                    diseaseActive = true;
                    break;
                }
            }
        }

        // Randomly select two populations for inter-population contact
        if (populations.size() > 1) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, populations.size() - 1);
            int popIndex1 = dis(gen);
            int popIndex2 = dis(gen);
            while (popIndex1 == popIndex2) {
                popIndex2 = dis(gen);
            }
            interPopulationContact(populations[popIndex1], populations[popIndex2]);
        }

        // Write simulation details for each timestep
        writeSimulationDetails("disease_details.csv", timestep, populations);

        timestep++;
    }

    // Calculate summary statistics
    int vaccinated = 0, recovered = 0, susceptible = 0;
    for (const auto& population : populations) {
        for (const auto& person : population.people) {
            switch (person.status) {
            case HealthStatus::Vaccinated: vaccinated++; break;
            case HealthStatus::Recovered: recovered++; break;
            case HealthStatus::Susceptible: susceptible++; break;
            default: break;
            }
        }
    }

    // Write summary statistics
    writeSummaryStatistics("disease_stats.csv", timestep, vaccinated, recovered, susceptible);

    // Print summary
    printSummary(timestep, vaccinated, recovered, susceptible);
}