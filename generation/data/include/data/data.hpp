#pragma once
#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>

class SphericalCoordinatesGenerator {
public:
    void writePointsToFile(const std::string &filename, const std::vector<std::vector<double>> &points) const;

    std::vector<std::vector<double>> readPointsFromFile(const std::string &filename) const;

    std::vector<std::vector<double>> generatePointsOnArc(int numPoints, double phi_start, double theta_start, double phi_end, double theta_end) const;

    std::vector<std::vector<double>> addCoordinateNoiseOnSphere(const std::vector<std::vector<double>> &points, double noiseLevel) const;

    std::vector<std::vector<double>> generatePointsFromCenter(int numArcs, int numPointsPerArc, double centerPhi, double centerTheta, double phi_start, double theta_start, double phi_end, double theta_end) const;
};

#endif // DATA_HPP

