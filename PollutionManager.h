#ifndef POLLUTIONMANAGER_H
#define POLLUTIONMANAGER_H

#include <vector>
#include "CityGrid.h"

class PollutionManager {
private:
    std::vector<std::vector<int>> pollutionMap;  // 2D grid for storing pollution levels
    int numRows, numCols;
    const int industrialPollutionRate = 5;   // Pollution rate for industrial zones
    const int commercialPollutionRate = 3;   // Pollution rate for commercial zones
    const int residentialPollutionRate = 1;  // Pollution rate for residential zones
    const float spreadFactor = 0.5;          // Pollution spread factor
    const float reductionFactor = 0.25;      // Pollution reduction factor in green zones

public:
    PollutionManager(int numRows, int numCols);
    void computePollution(const CityGrid& city);    // Compute pollution based on zone type
    void dispersePollution();                       // Disperse pollution to neighboring cells
    void mitigatePollution(const CityGrid& city);   // Mitigate pollution in green zones
    void refreshPollution(const CityGrid& city);    // Refresh pollution levels in the grid
    void displayPollutionMap();                     // Display the pollution map for analysis
};

#endif
