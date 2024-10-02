#ifndef SIMULATIONFILEREADER_H
#define SIMULATIONFILEREADER_H

#include "CityMap.h"
#include <string>

class SimulationFileReader {
private:
    std::string cityMapFile;   // Name of the city map file
    int maxSimulationTime;     // Total duration for the simulation
    int updateFrequency;       // How frequently the map should refresh

    bool mapCellInterpreter(const std::string& cellValue, std::string& zoneType) const;  // Helper function to interpret each cell value

public:
    SimulationFileReader(const std::string& configurationFile);

    bool readConfig();  // Load the configuration from the config file
    bool loadCityMap(CityMap& city);  // Load the city map into the CityMap
    void startSimulation(CityMap& city);  // Run the simulation

    int getMaxSimulationTime() const { return maxSimulationTime; }
    int getUpdateFrequency() const { return updateFrequency; }
};

#endif
