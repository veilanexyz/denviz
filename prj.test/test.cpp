#include <data/data.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 6) {
        std::cerr << "Usage: " << argv[0] << " <type> <numPoints> <blurCoefficient> <distributionMin> <distributionMax>" << std::endl;
        return 1;
    }

    std::string type = argv[1];
    int numPoints = std::stoi(argv[2]);
    double blurCoefficient = std::stod(argv[3]);
    double distributionMin = std::stod(argv[4]);
    double distributionMax = std::stod(argv[5]);

    if (type == "points") {
        generatePointsWithNoise(numPoints, blurCoefficient, distributionMin, distributionMax);
//        std::vector<CartesianCoordinates> readPoints = readPointsFromFile("noisy_points.txt");
//        for (const auto& coord : readPoints) {
//            std::cout << "x: " << coord.x << ", y: " << coord.y << std::endl;
//        }
    }

    else if (type == "segments") {
        generateSegments(numPoints, blurCoefficient, distributionMin, distributionMax);
//        std::vector<CartesianForSegmentsCoordinates> readVectors = readSegmentsFromFile("noisy_segments.txt");
//        for (const auto& coordinates : readVectors) {
//            std::cout << "x: " << coordinates.x << ", y: " << coordinates.y
//                      << ", x1: " << coordinates.x1 << ", y1: " << coordinates.y1 << std::endl;
//        }
    }

    else if (type == "parallel_segments") {
        generateParallelSegments(numPoints, blurCoefficient, distributionMin, distributionMax);
//        std::vector<CartesianForSegmentsCoordinates> readParallelSegments = readSegmentsFromFile("noisy_parallel_segments.txt");
//        for (const auto& coordinates : readParallelSegments) {
//            std::cout << "x: " << coordinates.x << ", y: " << coordinates.y
//                      << ", x1: " << coordinates.x1 << ", y1: " << coordinates.y1 << std::endl;
//        }
    }

    else if (type == "segments_from_point") {
        if (argc < 8) {
            std::cerr << "Usage for segments_from_point: " << argv[0] << "segments_from_point <numPoints> <blurCoefficient> <startPoint.x> <startPoint.y>" << std::endl;
            return 1;
        }

        CartesianCoordinates startPoint;
        startPoint.x = std::stod(argv[6]);
        startPoint.y = std::stod(argv[7]);

        generateSegmentsFromPoint(numPoints, blurCoefficient,distributionMin, distributionMax, startPoint);
        std::vector<CartesianForSegmentsCoordinates> readSegmentsFromPoint = readSegmentsFromFile("noisy_segments_from_point.txt");
//        for (const auto& coordinates : readSegmentsFromPoint ) {
//            std::cout << "x: " << coordinates.x << ", y: " << coordinates.y
//                      << ", x1: " << coordinates.x1 << ", y1: " << coordinates.y1 << std::endl;
//        }
    }

    else {
        std::cerr << "Invalid generation type: " << type << std::endl;
        return 1;
    }
    return 0;
}


