#include "SimulationFileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>  // For time delays

SimulationFileReader::SimulationFileReader(const std::string& configurationFile) {
    std::ifstream configFile(configurationFile);
    if (!configFile.is_open()) {
        throw std::runtime_error("Error: Could not open configuration file " + configurationFile);
    }

    std::string configFileDirectory;
    size_t lastSlash = configurationFile.find_last_of("/\\");
    if (lastSlash != std::string::npos) {
        configFileDirectory = configurationFile.substr(0, lastSlash + 1);
    }

    std::getline(configFile, cityMapFile);  // First line is the city map file name
    configFile >> maxSimulationTime >> updateFrequency;  // Read the simulation time limit and refresh rate
    cityMapFile = configFileDirectory + cityMapFile;

    configFile.close();
}

bool SimulationFileReader::readConfig() {
    return !cityMapFile.empty() && maxSimulationTime > 0 && updateFrequency > 0;
}

bool SimulationFileReader::mapCellInterpreter(const std::string& cellValue, std::string& zoneType) const {
    if (cellValue == "R") zoneType = "Residential";
    else if (cellValue == "C") zoneType = "Commercial";
    else if (cellValue == "I") zoneType = "Industrial";
    else if (cellValue == "-") zoneType = "Road";
    else if (cellValue == "T") zoneType = "Powerline";
    else if (cellValue == "#") zoneType = "PowerlineRoad";
    else if (cellValue == "P") zoneType = "PowerPlant";
    else return false;

    return true;
}

bool SimulationFileReader::loadCityMap(CityMap& city) {
    std::ifstream mapFile(cityMapFile);
    if (!mapFile.is_open()) {
        std::cerr << "Error: Could not open map file " << cityMapFile << std::endl;
        return false;
    }

    std::string rowContent;
    int rowIndex = 0;

    while (std::getline(mapFile, rowContent)) {
        std::stringstream ss(rowContent);
        std::string cellValue;
        int colIndex = 0;

        while (std::getline(ss, cellValue, ',')) {
            if (rowIndex >= city.totalRows() || colIndex >= city.totalCols()) {
                std::cerr << "Error: Map data out of bounds at row " << rowIndex << ", column " << colIndex << std::endl;
                continue;
            }

            std::string zoneType;
            if (mapCellInterpreter(cellValue, zoneType)) {
                MapCell cell = { rowIndex, colIndex, zoneType, 0, 0 };  // Initialize pollution and population to 0
                city.modifyCell(rowIndex, colIndex, cell);
            }
            else {
                std::cerr << "Warning: Invalid cell value at row " << rowIndex << ", column " << colIndex << std::endl;
            }
            colIndex++;
        }

        rowIndex++;
    }

    mapFile.close();
    return true;
}

void SimulationFileReader::startSimulation(CityMap& city) {
    int elapsedTime = 0;

    std::cout << "Simulation has started..." << std::endl;
    while (elapsedTime < maxSimulationTime) {
        if (elapsedTime % updateFrequency == 0) {
            std::cout << "Current Simulation Time: " << elapsedTime << std::endl;
            for (int row = 0; row < city.totalRows(); ++row) {
                for (int col = 0; col < city.totalCols(); ++col) {
                    const std::string& zoneType = city.getMapCell(row, col).zoneType;
                    char displayChar = ' ';

                    if (zoneType == "Residential") displayChar = 'R';
                    else if (zoneType == "Commercial") displayChar = 'C';
                    else if (zoneType == "Industrial") displayChar = 'I';
                    else if (zoneType == "Road") displayChar = '-';
                    else if (zoneType == "Powerline") displayChar = 'T';
                    else if (zoneType == "PowerlineRoad") displayChar = '#';
                    else if (zoneType == "PowerPlant") displayChar = 'P';
                    else displayChar = ' ';

                    std::cout << displayChar << " ";
                }
                std::cout << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        ++elapsedTime;
    }

    std::cout << "Simulation complete." << std::endl;
}
