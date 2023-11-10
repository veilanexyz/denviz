#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

enum VisualizationType {
    POINTS,
    ARCS,
    VECTORS
};

std::string getTypeName(VisualizationType visType) {
    switch (visType) {
        case POINTS:
            return "points";
        case ARCS:
            return "arcs";
        case VECTORS:
            return "vectors";
        default:
            return "unknown";
    }
}

std::vector<std::pair<double, double>> generatePoints(int numPoints) {
    std::vector<std::pair<double, double>> data;

    for (int i = 0; i < numPoints; ++i) {
        double r = 5.0 * (static_cast<double>(rand()) / RAND_MAX);
        double theta = 2.0 * M_PI * (static_cast<double>(rand()) / RAND_MAX);
        data.emplace_back(r, theta);
    }

    return data;
}

std::vector<std::pair<double, double>> generateArcs(int numArcs) {
    std::vector<std::pair<double, double>> data;

    for (int i = 0; i < numArcs; ++i) {
        double r = 5.0 * (static_cast<double>(rand()) / RAND_MAX);
        double theta1 = 2.0 * M_PI * (static_cast<double>(rand()) / RAND_MAX);
        double theta2 = 2.0 * M_PI * (static_cast<double>(rand()) / RAND_MAX);
        data.emplace_back(r, theta1);
        data.emplace_back(r, theta2);
    }

    return data;
}

std::vector<std::pair<double, double>> generateVectors(int numVectors) {
    std::vector<std::pair<double, double>> data;

    for (int i = 0; i < numVectors; ++i) {
        double r = 5.0 * (static_cast<double>(rand()) / RAND_MAX);
        double theta = 2.0 * M_PI * (static_cast<double>(rand()) / RAND_MAX);
        data.emplace_back(r, theta);
    }

    return data;
}

void writeToFile(const std::vector<std::pair<double, double>>& data, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        // Установка точности вывода до двух знаков после запятой
        file << std::fixed << std::setprecision(2);

        for (const auto& point : data) {
            file << point.first << " " << point.second << std::endl;
        }

        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

std::vector<std::pair<double, double>> generateData(int numObjects, VisualizationType visType) {
    if (visType == POINTS) {
        return generatePoints(numObjects);
    } else if (visType == ARCS) {
        return generateArcs(numObjects);
    } else if (visType == VECTORS) {
        return generateVectors(numObjects);
    } else {
        std::cerr << "Invalid visualization type" << std::endl;
        return {};
    }
}


bool isNumber(const std::string& str) {
    std::istringstream iss(str);
    double dummy;
    return static_cast<bool>(iss >> dummy);
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <visType> <numObjects>" << std::endl;
        return 1;
    }

    std::string visTypeString = argv[1];
    std::string numObjectsString = argv[2];

    if (!isNumber(numObjectsString)) {
        std::cerr << "Invalid input for numObjects: " << numObjectsString << std::endl;
        return 1;
    }

    int numObjects = std::stoi(numObjectsString);

    if (numObjects > 1000000) {
        std::cerr << "Error: numObjects exceeds the maximum allowed value (1000000)" << std::endl;
        return 1;
    }

    VisualizationType visType;

    if (visTypeString == "points") {
        visType = POINTS;
    } else if (visTypeString == "arcs") {
        visType = ARCS;
    } else if (visTypeString == "vectors") {
        visType = VECTORS;
    } else {
        std::cerr << "Invalid visualization type" << std::endl;
        return 1;
    }

    std::string typeName = getTypeName(visType);
    std::vector<std::pair<double, double>> data = generateData(numObjects, visType);

    writeToFile(data, typeName + "_data.txt");

    return 0;
}






