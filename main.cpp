#include "SimulationFileReader.h"
#include "CityMap.h"
#include <iostream>

int main() {
     //config file
    std::string configFilePath = "config1.txt";

    try {
        // Create an instance of the SimulationFileReader with the config file
        SimulationFileReader fileReader(configFilePath);

        // Load the configuration file (e.g., time limit and refresh rate)
        if (!fileReader.readConfig()) {
            std::cerr << "Error: Failed to load configuration." << std::endl;
            return 1;
        }

        // Assuming a grid size of 10x10 for testing
        int gridRows = 10;
        int gridCols = 10;
        CityMap cityMap(gridRows, gridCols);

        // Load the city map/region from the file
        if (!fileReader.loadCityMap(cityMap)) {
            std::cerr << "Error: Failed to load city map." << std::endl;
            return 1;
        }

        // Run the simulation using the loaded map and configuration
        fileReader.startSimulation(cityMap);
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
