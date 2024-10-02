#ifndef INDUSTRIALZONE_H
#define INDUSTRIALZONE_H

#include "CityGrid.h"

class IndustrialZone {
private:
    int availableWorkers;  // Number of available workers in the simulation
    const int requiredWorkersPerGrowth = 2;  // Workers needed for one population growth in an industrial cell

public:
    IndustrialZone();
    void processIndustrialZones(CityGrid& city);  // Process growth and pollution generation
    void growIndustrialCell(Cell& cell);  // Grow a single industrial cell if conditions are met
    void generatePollution(Cell& cell, int& pollutionLevel);  // Generate pollution in industrial zones
    void assignJobs(int workers);  // Assign workers to jobs
    int getAvailableWorkers() const { return availableWorkers; }
    void setAvailableWorkers(int workers) { availableWorkers = workers; }
};

#endif
#pragma once
