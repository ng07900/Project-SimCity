#include "PollutionManager.h"
#include <iostream>

PollutionManager::PollutionManager(int numRows, int numCols)
    : numRows(numRows), numCols(numCols), pollutionMap(numRows, std::vector<int>(numCols, 0)) {}


void PollutionManager::computePollution(const CityGrid& city) {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            std::string zone = city.getCell(row, col).zoneType;
            if (zone == "Industrial") {
                pollutionMap[row][col] += industrialPollutionRate;
            }
            else if (zone == "Commercial") {
                pollutionMap[row][col] += commercialPollutionRate;
            }
            else if (zone == "Residential") {
                pollutionMap[row][col] += residentialPollutionRate;
            }
        }
    }
}

void PollutionManager::dispersePollution() {
    std::vector<std::vector<int>> updatedMap = pollutionMap;

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            int pollutionLevel = pollutionMap[row][col];

            // Disperse pollution to adjacent cells
            if (row > 0) updatedMap[row - 1][col] += pollutionLevel * spreadFactor;   // Above
            if (row < numRows - 1) updatedMap[row + 1][col] += pollutionLevel * spreadFactor;   // Below
            if (col > 0) updatedMap[row][col - 1] += pollutionLevel * spreadFactor;   // Left
            if (col < numCols - 1) updatedMap[row][col + 1] += pollutionLevel * spreadFactor;   // Right
        }
    }
    pollutionMap = updatedMap;
}

void PollutionManager::mitigatePollution(const CityGrid& city) {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (city.getCell(row, col).zoneType == "Green") {
                // Mitigate pollution in adjacent cells
                if (row > 0) pollutionMap[row - 1][col] -= pollutionMap[row - 1][col] * reductionFactor;  // Above
                if (row < numRows - 1) pollutionMap[row + 1][col] -= pollutionMap[row + 1][col] * reductionFactor;  // Below
                if (col > 0) pollutionMap[row][col - 1] -= pollutionMap[row][col - 1] * reductionFactor;  // Left
                if (col < numCols - 1) pollutionMap[row][col + 1] -= pollutionMap[row][col + 1] * reductionFactor;  // Right
            }
        }
    }
}

void PollutionManager::refreshPollution(const CityGrid& city) {
    computePollution(city);
    dispersePollution();
    mitigatePollution(city);
}

void PollutionManager::displayPollutionMap() {
    for (const auto& row : pollutionMap) {
        for (int pollution : row) {
            std::cout << pollution << " ";
        }
        std::cout << std::endl;
    }
}
