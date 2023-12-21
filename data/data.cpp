#include <data/data.hpp>
#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>

SphericalCoordinatesGenerator::SphericalCoordinatesGenerator() {}

void SphericalCoordinatesGenerator::writePointsToFile(const std::string& filename, const std::vector<std::vector<double>>& points) const {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    for (const auto& point : points) {
        for (const auto& coord : point) {
            outFile << coord << " ";
        }
        outFile << std::endl;
    }

    outFile.close();
}

std::vector<std::vector<double>> SphericalCoordinatesGenerator::readPointsFromFile(const std::string& filename) const {
    std::ifstream inFile(filename);
    std::vector<std::vector<double>> points;

    if (!inFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return points;
    }

    double value;
    while (inFile >> value) {
        std::vector<double> point;
        point.push_back(value);

        if (inFile >> value) {
            point.push_back(value);
            points.push_back(point);
        } else {
            std::cerr << "Error reading points from file." << std::endl;
            inFile.close();
            return points;
        }
    }

    inFile.close();
    return points;
}

std::vector<std::vector<double>> SphericalCoordinatesGenerator::generatePointsOnArc(int numPoints, double phi_start, double theta_start, double phi_end, double theta_end) const {
    std::vector<std::vector<double>> points;

    if (phi_start < 0 || phi_start >= 2 * M_PI || theta_start < 0 || theta_start > M_PI ||
        phi_end < 0 || phi_end >= 2 * M_PI || theta_end < 0 || theta_end > M_PI) {
        std::cerr << "Invalid input: phi and theta should be in the range [0, 2 * PI] and [0, PI] respectively." << std::endl;
        return points;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < numPoints; ++i) {
        double t = dis(gen); // параметр времени
        double phi = phi_start + t * (phi_end - phi_start);
        double theta = theta_start + t * (theta_end - theta_start);

        phi = fmod(phi + 2 * M_PI, 2 * M_PI);
        theta = std::max(0.0, std::min(M_PI, theta));

        points.push_back({theta, phi});
    }

    return points;
}

std::vector<std::vector<double>> SphericalCoordinatesGenerator::addCoordinateNoiseOnSphere(const std::vector<std::vector<double>>& points, double noiseLevel) const {
    std::vector<std::vector<double>> noisyPoints;

    if (noiseLevel < 0) {
        std::cerr << "Invalid input: noiseLevel should be non-negative." << std::endl;
        return noisyPoints;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dis(0.0, noiseLevel);

    for (const auto& point : points) {
        double theta = point[0];
        double phi = point[1];

        double deltaTheta = dis(gen);
        double deltaPhi = dis(gen);

        theta += deltaTheta;
        phi += deltaPhi;

        phi = fmod(phi + 2 * M_PI, 2 * M_PI);
        theta = std::max(0.0, std::min(M_PI, theta));

        noisyPoints.push_back({theta, phi});
    }

    return noisyPoints;
}

std::vector<std::vector<double>> SphericalCoordinatesGenerator::generatePointsFromCenter(int numArcs, int numPointsPerArc, double centerPhi, double centerTheta, double phi_start, double theta_start, double phi_end, double theta_end) const {
    std::vector<std::vector<double>> points;

    if (phi_start < 0 || phi_start >= 2 * M_PI || theta_start < 0 || theta_start > M_PI ||
        phi_end < 0 || phi_end >= 2 * M_PI || theta_end < 0 || theta_end > M_PI) {
        std::cerr << "Invalid input: phi and theta should be in the range [0, 2 * PI] and [0, PI] respectively." << std::endl;
        return points;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int arc = 0; arc < numArcs; ++arc) {
        std::vector<std::vector<double>> arcPoints;

        for (int i = 0; i < numPointsPerArc; ++i) {
            double t_phi = dis(gen);   // параметр времени для azimuthal угла
            double t_theta = dis(gen); // параметр времени для polar угла

            double phi = centerPhi + phi_start + t_phi * (phi_end - phi_start);
            double theta = centerTheta + theta_start + t_theta * (theta_end - theta_start);

            phi = fmod(phi + 2 * M_PI, 2 * M_PI);
            theta = std::max(0.0, std::min(M_PI, theta));

            arcPoints.push_back({theta, phi});
        }

        points.insert(points.end(), arcPoints.begin(), arcPoints.end());
    }

    return points;
}




