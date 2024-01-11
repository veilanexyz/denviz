#pragma once
#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>

struct Point {
    double phi;
    double theta;

    Point(double phi, double theta) : phi(phi), theta(theta) {}
};

class SphericalCoordinatesGenerator {
public:
    void writePointsToFile(const std::string& filename, const std::vector<Point>& points) const;

    std::vector<Point> readPointsFromFile(const std::string& filename) const;

    std::vector<Point> generatePointsOnArc(int numPoints, double phi_start, double theta_start, double phi_end, double theta_end) const;

    std::vector<Point> addCoordinateNoiseOnSphere(const std::vector<Point>& points, double noiseLevel) const;

    std::vector<Point> generatePointsFromCenter(int numArcs, int numPointsPerArc, double centerPhi, double centerTheta, double phi_start, double theta_start, double phi_end, double theta_end) const;
};

#endif // DATA_HPP
