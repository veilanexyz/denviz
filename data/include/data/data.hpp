#pragma once
#ifndef DENVIZ_DATA_H
#define DENVIZ_DATA_H

#include <vector>
#include <fstream>
#include <string>

struct CartesianCoordinates {
    double x;
    double y;
};
struct CartesianForSegmentsCoordinates {
    double x, y, x1, y1;
};

CartesianCoordinates addGaussianNoise(const CartesianCoordinates& original, double stddev);

CartesianCoordinates generateRandomPoint(double distributionMin, double distributionMax);

void writePointsToFile(const std::vector<CartesianCoordinates>& coordinates, const std::string& filename);

void writeSegmentsToFile(const std::vector<CartesianCoordinates>& coordinates, const std::string& filename);

void generatePointsWithNoise(int numPoints, double blurCoefficient, double distributionMin, double distributionMax);

void generateParallelSegments(int numSegments, double stddev, double distributionMin, double distributionMax);

void generateSegmentsFromPoint(int numSegments, double stddev, double distributionMin, double distributionMax, const CartesianCoordinates& startPoint);

void generateSegments(int numSegments, double stddev, double distributionMin, double distributionMax);

std::vector<CartesianCoordinates> readPointsFromFile(const char* filename);

std::vector<CartesianForSegmentsCoordinates> readSegmentsFromFile(const char* filename);

#endif //DENVIZ_DATA_H

