#include "CityGrid.h"

CityGrid::CityGrid(int rows, int cols) {
    grid.resize(rows, std::vector<Cell>(cols));
}

Cell CityGrid::getCell(int x, int y) const {
    return grid[x][y];
}

void CityGrid::updateCell(int x, int y, const Cell& cell) {
    grid[x][y] = cell;
}
