#include "IndustrialZone.h"
#include <iostream>

IndustrialZone::IndustrialZone() : availableWorkers(0) {}

void IndustrialZone::processIndustrialZones(CityGrid& city) {
    for (int i = 0; i < city.getRows(); i++) {
        for (int j = 0; j < city.getCols(); j++) {
            Cell cell = city.getCell(i, j);

            if (cell.zoneType == "Industrial") {
                // Grow industrial cell if conditions are met
                growIndustrialCell(cell);

                // Generate pollution for industrial zones
                int pollution = 0;
                generatePollution(cell, pollution);
                cell.pollutionLevel += pollution;
            }
        }
    }
}

void IndustrialZone::growIndustrialCell(Cell& cell) {
    // Industrial cells grow if there are enough workers
    if (cell.populationCapacity < 3 && availableWorkers >= requiredWorkersPerGrowth) {
        cell.populationCapacity++;
        availableWorkers -= requiredWorkersPerGrowth;
        std::cout << "Industrial cell grew at (" << cell.x << ", " << cell.y << "). Population: "
            << cell.populationCapacity << std::endl;
    }
}

void IndustrialZone::generatePollution(Cell& cell, int& pollutionLevel) {
    // Pollution generated is equal to the population of the industrial zone
    pollutionLevel = cell.populationCapacity * 5;  // Example: each population point produces 5 pollution units
    std::cout << "Generated pollution: " << pollutionLevel << " at (" << cell.x << ", " << cell.y << ")" << std::endl;
}

void IndustrialZone::assignJobs(int workers) {
    availableWorkers = workers;
}
