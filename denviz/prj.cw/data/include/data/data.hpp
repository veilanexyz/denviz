#ifndef DENVIZ_DATA_H
#define DENVIZ_DATA_H
#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

enum VisualizationType {
    POINTS,
    ARCS,
    VECTORS
};

struct PolarDataPoint {
    double radius, angle;
};

struct CoordinateLimits {
    double maxRadius;
    double maxAngle;
};

std::string getTypeName(VisualizationType visType);

std::vector<PolarDataPoint> generatePointsWithNoise(int numPoints, const CoordinateLimits& limits, double noiseLevel);

std::vector<PolarDataPoint> generateArcsWithNoise(int numArcs, const CoordinateLimits& limits, double noiseLevel);

std::vector<PolarDataPoint> generateVectorsWithNoise(int numVectors, const CoordinateLimits& limits, double noiseLevel);

void writeVectorsToFile(const std::vector<PolarDataPoint>& data, const std::string& filename);

std::vector<PolarDataPoint> readVectorsFromFile(const std::string& filename);

void writePointsToFile(const std::vector<PolarDataPoint>& data, const std::string& filename);

std::vector<PolarDataPoint> readPointsFromFile(const std::string& filename);

void writeArcsToFile(const std::vector<double>& data, const std::string& filename);

std::vector<double> readArcsFromFile(const std::string& filename);

void drawPoints(const std::vector<PolarDataPoint>& polarPoints, sf::RenderWindow& window, double scaleFactor);

void drawVectors(const std::vector<PolarDataPoint>& polarPoints, sf::RenderWindow& window, double scaleFactor);

void drawArcs(const std::vector<double>& arcData, sf::RenderWindow& window, double scaleFactor);

void saveToPNG(const sf::RenderWindow& window, const std::string& filename);

#endif //DENVIZ_DATA_H
