#include <data/data.hpp>
#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>

CartesianCoordinates addGaussianNoise(const CartesianCoordinates& original, double stddev) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::normal_distribution<double> distribution(0.0, stddev);

    CartesianCoordinates noisy;
    noisy.x = original.x + distribution(gen);
    noisy.y = original.y + distribution(gen);
    return noisy;
}

CartesianCoordinates generateRandomPoint(double distributionMin, double distributionMax) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(distributionMin, distributionMax);

    CartesianCoordinates point;
    point.x = distribution(gen);
    point.y = distribution(gen);
    return point;
}

void writePointsToFile(const std::vector<CartesianCoordinates>& coordinates, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    outFile << std::fixed << std::setprecision(2);

    for (const auto& point : coordinates) {
        outFile << point.x << ' ' << point.y << '\n';
    }
    outFile.close();
}

void writeSegmentsToFile(const std::vector<CartesianCoordinates>& coordinates, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    outFile << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < coordinates.size(); i += 2) {
        outFile << coordinates[i].x << " " << coordinates[i].y << " ";
        outFile << coordinates[i + 1].x << " " << coordinates[i + 1].y << std::endl;
    }

    outFile.close();
}


void generatePointsWithNoise(int numPoints, double blurCoefficient, double distributionMin, double distributionMax) {
    std::vector<CartesianCoordinates> noisyPoints;
    std::vector<CartesianCoordinates> cleanPoints;
    std::vector<CartesianCoordinates> differences;

    for (int i = 0; i < numPoints; ++i) {
        CartesianCoordinates cleanPoint = generateRandomPoint(distributionMin, distributionMax);
        CartesianCoordinates noisyPoint = addGaussianNoise(cleanPoint, blurCoefficient);

        cleanPoints.push_back(cleanPoint);
        noisyPoints.push_back(noisyPoint);

        CartesianCoordinates diff;
        diff.x = noisyPoint.x - cleanPoint.x;
        diff.y = noisyPoint.y - cleanPoint.y;
        differences.push_back(diff);
    }

    // Write clean points, noisy points, and differences to files
    writePointsToFile(cleanPoints, "clean_points.txt");
    writePointsToFile(noisyPoints, "noisy_points.txt");
    writePointsToFile(differences, "difference_points.txt");

}


void generateParallelSegments(int numSegments, double stddev, double distributionMin, double distributionMax) {
    std::vector<CartesianCoordinates> cleanSegments;
    std::vector<CartesianCoordinates> noisySegments;
    std::vector<CartesianCoordinates> differences;

    for (int i = 0; i < numSegments; ++i) {
        CartesianCoordinates cleanStartPoint = generateRandomPoint(distributionMin, distributionMax);
        CartesianCoordinates cleanEndPoint = generateRandomPoint(distributionMin, distributionMax);

        CartesianCoordinates noisyStartPoint = addGaussianNoise(cleanStartPoint, stddev);
        CartesianCoordinates noisyEndPoint = addGaussianNoise(cleanEndPoint, stddev);

        cleanSegments.push_back(cleanStartPoint);
        cleanSegments.push_back(cleanEndPoint);

        noisySegments.push_back(noisyStartPoint);
        noisySegments.push_back(noisyEndPoint);

        CartesianCoordinates diffStartPoint;
        diffStartPoint.x = noisyStartPoint.x - cleanStartPoint.x;
        diffStartPoint.y = noisyStartPoint.y - cleanStartPoint.y;
        differences.push_back(diffStartPoint);

        CartesianCoordinates diffEndPoint;
        diffEndPoint.x = noisyEndPoint.x - cleanEndPoint.x;
        diffEndPoint.y = noisyEndPoint.y - cleanEndPoint.y;
        differences.push_back(diffEndPoint);
    }

    writeSegmentsToFile(cleanSegments, "clean_segments.txt");
    writeSegmentsToFile(noisySegments, "noisy_segments.txt");
    writeSegmentsToFile(differences, "difference_segments.txt");

}

void generateSegmentsFromPoint(int numSegments, double stddev, double distributionMin, double distributionMax, const CartesianCoordinates& startPoint) {
    std::vector<CartesianCoordinates> cleanSegments;
    std::vector<CartesianCoordinates> noisySegments;
    std::vector<CartesianCoordinates> differences;

    for (int i = 0; i < numSegments; ++i) {
        CartesianCoordinates cleanEndPoint = generateRandomPoint(distributionMin, distributionMax);

        CartesianCoordinates noisyEndPoint = addGaussianNoise(cleanEndPoint, stddev);

        cleanSegments.push_back(startPoint);
        cleanSegments.push_back(cleanEndPoint);

        noisySegments.push_back(startPoint);
        noisySegments.push_back(noisyEndPoint);

        CartesianCoordinates diffEndPoint;
        diffEndPoint.x = noisyEndPoint.x - cleanEndPoint.x;
        diffEndPoint.y = noisyEndPoint.y - cleanEndPoint.y;
        differences.push_back(diffEndPoint);
    }

    writeSegmentsToFile(cleanSegments, "clean_segments_from_point.txt");
    writeSegmentsToFile(noisySegments, "noisy_segments_from_point.txt");
    writeSegmentsToFile(differences, "difference_segments_from_point.txt");

}

void generateSegments(int numSegments, double stddev, double distributionMin, double distributionMax) {
    std::vector<CartesianCoordinates> cleanSegments;
    std::vector<CartesianCoordinates> noisySegments;
    std::vector<CartesianCoordinates> differences;

    for (int i = 0; i < numSegments; ++i) {
        CartesianCoordinates cleanStartPoint = generateRandomPoint(distributionMin, distributionMax);
        CartesianCoordinates cleanEndPoint = generateRandomPoint(distributionMin, distributionMax);

        CartesianCoordinates noisyStartPoint = addGaussianNoise(cleanStartPoint, stddev);
        CartesianCoordinates noisyEndPoint = addGaussianNoise(cleanEndPoint, stddev);

        // Save clean and noisy segments
        cleanSegments.push_back(cleanStartPoint);
        cleanSegments.push_back(cleanEndPoint);

        noisySegments.push_back(noisyStartPoint);
        noisySegments.push_back(noisyEndPoint);

        // Calculate and save the difference
        CartesianCoordinates diffStartPoint;
        diffStartPoint.x = noisyStartPoint.x - cleanStartPoint.x;
        diffStartPoint.y = noisyStartPoint.y - cleanStartPoint.y;
        differences.push_back(diffStartPoint);

        CartesianCoordinates diffEndPoint;
        diffEndPoint.x = noisyEndPoint.x - cleanEndPoint.x;
        diffEndPoint.y = noisyEndPoint.y - cleanEndPoint.y;
        differences.push_back(diffEndPoint);
    }

    writeSegmentsToFile(cleanSegments, "clean_segments.txt");
    writeSegmentsToFile(noisySegments, "noisy_segments.txt");
    writeSegmentsToFile(differences, "difference_segments.txt");
}


std::vector<CartesianCoordinates> readPointsFromFile(const char* filename) {
    std::vector<CartesianCoordinates> coordinates;
    double x, y;

    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка при открытии файла." << std::endl;
        return coordinates;
    }

    while (inputFile >> x >> y) {
        CartesianCoordinates coord{ x, y };
        coordinates.push_back(coord);
    }

    inputFile.close();
    return coordinates;
}

std::vector<CartesianForSegmentsCoordinates> readSegmentsFromFile(const char* filename) {
    std::vector<CartesianForSegmentsCoordinates> vectors;
    double x, y, z, w;

    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка при открытии файла." << std::endl;
        return vectors;
    }

    while (inputFile >> x >> y >> z >> w) {
        CartesianForSegmentsCoordinates coordinates{ x, y, z, w };
        vectors.push_back(coordinates);
    }

    inputFile.close();
    return vectors;
}

