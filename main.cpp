#include "CityGrid.h"
#include "PollutionManager.h"
#include "IndustrialZone.h"
#include <iostream>

int main() {
    // Define grid dimensions
    const int numRows = 5;
    const int numCols = 5;

    // Create a CityGrid (initialize cells with default values)
    CityGrid city(numRows, numCols);

    // Initialize the grid with different zones for testing
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            Cell cell;
            cell.x = i;
            cell.y = j;
            cell.pollutionLevel = 0;      // Set initial pollution to 0
            cell.populationCapacity = 0;  // Set initial population capacity to 0

            if (i == 0 && j == 0) {
                cell.zoneType = "Industrial";
            }
            else if (i == 0 && j == 1) {
                cell.zoneType = "Commercial";
            }
            else if (i == 0 && j == 2) {
                cell.zoneType = "Residential";
            }
            else if (i == 1 && j == 0) {
                cell.zoneType = "Green";
            }
            else if (i == 1 && j == 1) {
                cell.zoneType = "Industrial";
            }
            else if (i == 2 && j == 2) {
                cell.zoneType = "Green";
            }
            else {
                cell.zoneType = "Residential";
            }
            city.updateCell(i, j, cell);  // Update cell in the city grid
        }
    }

    // Create a PollutionManager
    PollutionManager pollutionManager(numRows, numCols);

    // Create an IndustrialZone object and assign workers
    IndustrialZone industrialZone;
    industrialZone.assignJobs(10);  // Assign 10 workers for testing

    // Process industrial zones to generate pollution and manage growth
    industrialZone.processIndustrialZones(city);

    // Run the pollution management logic
    pollutionManager.refreshPollution(city);

    // Display the pollution map
    std::cout << "Pollution Map After Processing:" << std::endl;
    pollutionManager.displayPollutionMap();

    // Run the pollution management logic
    pollutionManager.refreshPollution(city);

    std::cout << "Pollution Map After Processing:" << std::endl;
    pollutionManager.displayPollutionMap();

    return 0;
}
