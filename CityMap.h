#pragma once
#ifndef CITYMAP_H
#define CITYMAP_H

#include <vector>
#include <string>

struct MapCell {
    int row, col;  // Coordinates in the grid
    std::string zoneType;  // Type of the zone (Residential, Commercial, etc.)
    int pollutionLevel;  // Initial pollution level (set to 0)
    int populationCapacity;  // Maximum population capacity or jobs

};

class CityMap {
private:
    std::vector<std::vector<MapCell>> gridMatrix;

public:
    CityMap(int gridRows, int gridCols);
    MapCell getMapCell(int row, int col) const;
    void modifyCell(int row, int col, const MapCell& cell);
    int totalRows() const { return gridMatrix.size(); }
    int totalCols() const { return gridMatrix[0].size(); }
};

#endif
