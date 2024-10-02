#include "CityMap.h"

CityMap::CityMap(int gridRows, int gridCols) {
    gridMatrix.resize(gridRows, std::vector<MapCell>(gridCols));
}

MapCell CityMap::getMapCell(int row, int col) const {
    return gridMatrix[row][col];
}

void CityMap::modifyCell(int row, int col, const MapCell& cell) {
    gridMatrix[row][col] = cell;
}
