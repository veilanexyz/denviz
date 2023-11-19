#pragma once
#include <data/data.hpp>
#include<iostream>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <type> <numPoints> <blurCoefficient>" << std::endl;
        return 1;
    }

    std::string type = argv[1];
    int numPoints = std::stoi(argv[2]);
    double blurCoefficient = std::stod(argv[3]);

    if (type == "points") {
        std::vector<SphericalCoordinates> sphericalCoordinates = generateSphericalCoordinates(numPoints);
        std::vector<SphericalCoordinates> noisySphericalCoordinates;
        double sphericalNoiseStdDev = blurCoefficient;
        for (const auto& spherical : sphericalCoordinates) {
            SphericalCoordinates noisySpherical = addGaussianNoiseToSpherical(spherical, sphericalNoiseStdDev);
            noisySphericalCoordinates.push_back(noisySpherical);
        }
        std::vector<CartesianCoordinates> noisyCartesianCoordinates;
        double cartesianNoiseStdDev = blurCoefficient;
        for (const auto& spherical : noisySphericalCoordinates) {
            CartesianCoordinates cartesian = sphericalToCartesian(spherical, 1.0);
            CartesianCoordinates noisyCartesian = addGaussianNoiseToCartesian(cartesian, cartesianNoiseStdDev);
            noisyCartesianCoordinates.push_back(noisyCartesian);
        }

        writeSphericalToFile(noisySphericalCoordinates, "noisy_spherical.txt");
        writeCartesianToFile(noisyCartesianCoordinates, "noisy_cartesian.txt");
        //
    } else if (type == "vectors") {
        std::vector<SphericalCoordinates> vectorCoordinates = generateSphericalCoordinates(numPoints * 2);

        std::vector<SphericalCoordinates> noisySphericalCoordinates;
        double sphericalNoiseStdDev = blurCoefficient;
        for (const auto& spherical : vectorCoordinates) {
            SphericalCoordinates noisySpherical = addGaussianNoiseToSpherical(spherical, sphericalNoiseStdDev);
            noisySphericalCoordinates.push_back(noisySpherical);
        }

        std::vector<CartesianCoordinates> noisyCartesianCoordinates;
        double cartesianNoiseStdDev = blurCoefficient;
        for (const auto& spherical : noisySphericalCoordinates) {
            CartesianCoordinates cartesian = sphericalToCartesian(spherical, 1.0);
            CartesianCoordinates noisyCartesian = addGaussianNoiseToCartesian(cartesian, cartesianNoiseStdDev);
            noisyCartesianCoordinates.push_back(noisyCartesian);
        }

        writeSphericalVectorsToFile(noisySphericalCoordinates, "noisy_spherical_vectors.txt");
        writeCartesianVectorsToFile(noisyCartesianCoordinates, "noisy_cartesian_vectors.txt");
    } else if (type == "parallel_segments") {
        if (argc < 6) {
            std::cerr << "Usage for parallel_segments: " << argv[0] << " parallel_segments <numPoints> <blurCoefficient> <minLength> <maxLength>" << std::endl;
            return 1;
        }

        double minLength = std::stod(argv[4]);
        double maxLength = std::stod(argv[5]);

        std::vector<SphericalCoordinates> noisyParallelSegments = generateNoisyParallelSegments(numPoints * 2, minLength, maxLength, blurCoefficient);
        std::vector<CartesianCoordinates> noisyParallelSegmentsCartesian = generateNoisyParallelSegmentsCartesian(numPoints * 2, minLength, maxLength, blurCoefficient);

        writeSphericalVectorsToFile(noisyParallelSegments, "noisy_parallel_segments_spherical.txt");
        writeCartesianVectorsToFile(noisyParallelSegmentsCartesian, "noisy_parallel_segments_cartesian.txt");
    } else if (type == "segments_from_point") {
        if (argc < 8) {
            std::cerr << "Usage for segments_from_point: " << argv[0] << " segments_from_point <numPoints> <blurCoefficient> <minLength> <maxLength> <startPoint.theta> <startPoint.phi>" << std::endl;
            return 1;
            }

        SphericalCoordinates startPoint;
        startPoint.theta = std::stod(argv[6]);
        startPoint.phi = std::stod(argv[7]);
        double minLength = std::stod(argv[4]);
        double maxLength = std::stod(argv[5]);


        std::vector<SphericalCoordinates> noisySegmentsFromPointSpherical = generateSegmentsFromPointSpherical(numPoints, minLength, maxLength, blurCoefficient, startPoint);
        std::vector<CartesianCoordinates> noisySegmentsFromPointCartesian = generateSegmentsFromPointCartesian(numPoints, minLength, maxLength, blurCoefficient, startPoint);

        writeSphericalVectorsToFile(noisySegmentsFromPointSpherical, "noisy_segments_from_point_spherical.txt");
        writeCartesianVectorsToFile(noisySegmentsFromPointCartesian, "noisy_segments_from_point_cartesian.txt");
    } else {
        std::cerr << "Invalid generation type: " << type << std::endl;
        return 1;
    }

    return 0;
}

//int main() {
//    int numPoints = 1000;
//    std::string type = "vectors";
//    if (type == "points") {
//        std::vector<SphericalCoordinates> sphericalCoordinates = generateSphericalCoordinates(numPoints);
//        std::vector<SphericalCoordinates> noisySphericalCoordinates;
//        double sphericalNoiseStdDev = 0.1;
//        for (const auto& spherical : sphericalCoordinates) {
//            SphericalCoordinates noisySpherical = addGaussianNoiseToSpherical(spherical, sphericalNoiseStdDev);
//            noisySphericalCoordinates.push_back(noisySpherical);
//        }
//        std::vector<CartesianCoordinates> noisyCartesianCoordinates;
//        double cartesianNoiseStdDev = 0.1; // уровень шума
//        for (const auto& spherical : noisySphericalCoordinates) {
//            CartesianCoordinates cartesian = sphericalToCartesian(spherical, 1.0);
//            CartesianCoordinates noisyCartesian = addGaussianNoiseToCartesian(cartesian, cartesianNoiseStdDev);
//            noisyCartesianCoordinates.push_back(noisyCartesian);
//        }
//
//        writeSphericalToFile(noisySphericalCoordinates, "noisy_spherical.txt");
//        writeCartesianToFile(noisyCartesianCoordinates, "noisy_cartesian.txt");
//    }
//
//    else if (type == "vectors") {
//        std::vector<SphericalCoordinates> vectorCoordinates = generateSphericalCoordinates(numPoints * 2);
//
//        std::vector<SphericalCoordinates> noisySphericalCoordinates;
//        double sphericalNoiseStdDev = 0.1;
//        for (const auto& spherical : vectorCoordinates) {
//            SphericalCoordinates noisySpherical = addGaussianNoiseToSpherical(spherical, sphericalNoiseStdDev);
//            noisySphericalCoordinates.push_back(noisySpherical);
//        }
//
//        std::vector<CartesianCoordinates> noisyCartesianCoordinates;
//        double cartesianNoiseStdDev = 0.1; // уровень шума
//        for (const auto& spherical : noisySphericalCoordinates) {
//            CartesianCoordinates cartesian = sphericalToCartesian(spherical, 1.0);
//            CartesianCoordinates noisyCartesian = addGaussianNoiseToCartesian(cartesian, cartesianNoiseStdDev);
//            noisyCartesianCoordinates.push_back(noisyCartesian);
//        }
//
//        writeSphericalVectorsToFile(noisySphericalCoordinates, "noisy_spherical_vectors.txt");
//        writeCartesianVectorsToFile(noisyCartesianCoordinates, "noisy_cartesian_vectors.txt");
//    }
//
//    else if(type == "parallel segments"){
//        std::vector<SphericalCoordinates> noisyParallelSegments = generateNoisyParallelSegments(numPoints * 2, 1.0, 2.0, 0.1);
//        std::vector<CartesianCoordinates> noisyParallelSegmentsCartesian = generateNoisyParallelSegmentsCartesian(numPoints * 2, 1.0 , 2.0, 0.1);
//
//        writeSphericalVectorsToFile(noisyParallelSegments, "noisy_parallel_segments_spherical.txt");
//        writeCartesianVectorsToFile(noisyParallelSegmentsCartesian, "noisy_parallel_segments_cartesian.txt");
//    }
//
//    else if(type == "segments from point"){
//        SphericalCoordinates startPoint;
//        startPoint.theta = 1.5;
//        startPoint.phi = 0.8;
//        std::vector<SphericalCoordinates> noisySegmentsFromPointSpherical = generateSegmentsFromPointSpherical(numPoints, 1.0, 2.0, 0.1, startPoint);
//
//            std::vector<CartesianCoordinates> noisySegmentsFromPointCartesian = generateSegmentsFromPointCartesian(numPoints, 1.0, 2.0, 0.1, startPoint);
//
//            writeSphericalVectorsToFile(noisySegmentsFromPointSpherical, "noisy_segments_from_point_spherical.txt");
//            writeCartesianVectorsToFile(noisySegmentsFromPointCartesian, "noisy_segments_from_point_cartesian.txt");
//        }
//    return 0;
//}


