#pragma once

#ifndef DATA_DATA_HPP
#define DATA_DATA_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <random>

struct SphericalCoordinates {
    double theta;
    double phi;
};

struct CartesianCoordinates {
    double x;
    double y;
    double z;
};

std::vector<SphericalCoordinates> generateSphericalCoordinates(int numPoints);

CartesianCoordinates sphericalToCartesian(const SphericalCoordinates& spherical, double radius);

SphericalCoordinates addGaussianNoiseToSpherical(const SphericalCoordinates& original, double stddev);

CartesianCoordinates addGaussianNoiseToCartesian(const CartesianCoordinates& original, double stddev);

std::vector<SphericalCoordinates> generateNoisyParallelSegments(int numSegments, double minLength, double maxLength, double stddev);

std::vector<CartesianCoordinates> generateNoisyParallelSegmentsCartesian(int numSegments, double minLength, double maxLength, double stddev);

std::vector<SphericalCoordinates> generateSegmentsFromPointSpherical(int numSegments, double minLength, double maxLength, double stddev, const SphericalCoordinates& startPoint);

std::vector<CartesianCoordinates> generateSegmentsFromPointCartesian(int numSegments, double minLength, double maxLength, double stddev, const SphericalCoordinates& startSphericalPoint);

void writeSphericalToFile(const std::vector<SphericalCoordinates>& coordinates, const std::string& filename);

void writeSphericalVectorsToFile(const std::vector<SphericalCoordinates>& coordinates, const std::string& filename);

void writeCartesianVectorsToFile(const std::vector<CartesianCoordinates>& coordinates, const std::string& filename);

std::vector<SphericalCoordinates> readSphericalFromFile(const std::string& filename);

std::vector<CartesianCoordinates> readCartesianVectorsFromFile(const std::string& filename);

std::vector<SphericalCoordinates> readSphericalVectorsFromFile(const std::string& filename);

void writeCartesianToFile(const std::vector<CartesianCoordinates>& coordinates, const std::string& filename);

std::vector<CartesianCoordinates> readCartesianFromFile(const std::string& filename);

#endif //DATA_DATA_HPP
