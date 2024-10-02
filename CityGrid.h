#pragma once
#ifndef CITYGRID_H
#define CITYGRID_H

#include <vector>
#include <string>

struct Cell {
    int x, y;  // Coordinates
    std::string zoneType;  // Type of the zone (Residential, Commercial, etc.)
    int pollutionLevel;  // Initial pollution level (set to 0)
    int populationCapacity;  // Population capacity or jobs
   
};

class CityGrid {
private:
    std::vector<std::vector<Cell>> grid;

public:
    CityGrid(int rows, int cols);
    Cell getCell(int x, int y) const;
    void updateCell(int x, int y, const Cell& cell);
    int getRows() const { return grid.size(); }
    int getCols() const { return grid[0].size(); }
};

#endif
