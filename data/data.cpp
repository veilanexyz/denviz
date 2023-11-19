#include <data/data.hpp>
#include <fstream>

std::vector<SphericalCoordinates> generateSphericalCoordinates(int numPoints) {
    std::vector<SphericalCoordinates> coordinates;
    for (int i = 0; i < numPoints; ++i) {
        SphericalCoordinates point;
        point.theta = 2 * M_PI * (static_cast<double>(rand()) / RAND_MAX);
        point.phi = acos(2 * (static_cast<double>(rand()) / RAND_MAX) - 1);
        coordinates.push_back(point);
    }
    return coordinates;
}

CartesianCoordinates sphericalToCartesian(const SphericalCoordinates& spherical, double radius = 1.0) {
    CartesianCoordinates cartesian;
    cartesian.x = radius * sin(spherical.phi) * cos(spherical.theta);
    cartesian.y = radius * sin(spherical.phi) * sin(spherical.theta);
    cartesian.z = radius * cos(spherical.phi);
    return cartesian;
}

SphericalCoordinates addGaussianNoiseToSpherical(const SphericalCoordinates& original, double stddev) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, stddev);//математическое ожидание, стандартное отклонение.

    SphericalCoordinates noisy;
    noisy.theta = original.theta + distribution(gen);
    noisy.phi = original.phi + distribution(gen);

    return noisy;
}

CartesianCoordinates addGaussianNoiseToCartesian(const CartesianCoordinates& original, double stddev) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, stddev);

    CartesianCoordinates noisy;
    noisy.x = original.x + distribution(gen);
    noisy.y = original.y + distribution(gen);
    noisy.z = original.z + distribution(gen);

    return noisy;
}

std::vector<SphericalCoordinates> generateNoisyParallelSegments(int numSegments, double minLength, double maxLength, double stddev) {
    std::vector<SphericalCoordinates> baseCoordinates = generateSphericalCoordinates(numSegments);
    std::vector<SphericalCoordinates> noisySegments;

    for (const auto& baseCoord : baseCoordinates) {
        double segmentLength = minLength + (maxLength - minLength) * (static_cast<double>(rand()) / RAND_MAX);
        SphericalCoordinates startPoint = baseCoord;
        SphericalCoordinates endPoint = addGaussianNoiseToSpherical(baseCoord, stddev);
        endPoint.phi = std::min(M_PI, endPoint.phi + segmentLength);  // Ensure phi does not exceed PI

        noisySegments.push_back(startPoint);
        noisySegments.push_back(endPoint);
    }

    return noisySegments;
}

std::vector<CartesianCoordinates> generateNoisyParallelSegmentsCartesian(int numSegments, double minLength, double maxLength, double stddev) {
    std::vector<SphericalCoordinates> baseCoordinates = generateSphericalCoordinates(numSegments);
    std::vector<CartesianCoordinates> noisySegments;

    for (const auto& baseCoord : baseCoordinates) {
        double segmentLength = minLength + (maxLength - minLength) * (static_cast<double>(rand()) / RAND_MAX);
        CartesianCoordinates startPoint = sphericalToCartesian(baseCoord);
        CartesianCoordinates endPoint = sphericalToCartesian(addGaussianNoiseToSpherical(baseCoord, stddev), segmentLength);

        startPoint = addGaussianNoiseToCartesian(startPoint, stddev);
        endPoint = addGaussianNoiseToCartesian(endPoint, stddev);

        noisySegments.push_back(startPoint);
        noisySegments.push_back(endPoint);
    }

    return noisySegments;
}

std::vector<SphericalCoordinates> generateSegmentsFromPointSpherical(int numSegments, double minLength, double maxLength, double stddev, const SphericalCoordinates& startPoint) {
    std::vector<SphericalCoordinates> segments;

    for (int i = 0; i < numSegments; ++i) {
        double segmentLength = minLength + (maxLength - minLength) * (static_cast<double>(rand()) / RAND_MAX);
        SphericalCoordinates endPoint = addGaussianNoiseToSpherical(startPoint, stddev);
        endPoint.phi = std::min(M_PI, endPoint.phi + segmentLength);  // Ensure phi does not exceed PI

        segments.push_back(startPoint);
        segments.push_back(endPoint);
    }

    return segments;
}

std::vector<CartesianCoordinates> generateSegmentsFromPointCartesian(int numSegments, double minLength, double maxLength, double stddev, const SphericalCoordinates& startSphericalPoint) {
    std::vector<CartesianCoordinates> segments;

    for (int i = 0; i < numSegments; ++i) {
        double segmentLength = minLength + (maxLength - minLength) * (static_cast<double>(rand()) / RAND_MAX);

        SphericalCoordinates noisySpherical = addGaussianNoiseToSpherical(startSphericalPoint, stddev);

        CartesianCoordinates startPoint = sphericalToCartesian(noisySpherical);
        CartesianCoordinates endPoint = sphericalToCartesian(addGaussianNoiseToSpherical(noisySpherical, stddev), segmentLength);

        startPoint = addGaussianNoiseToCartesian(startPoint, stddev);
        endPoint = addGaussianNoiseToCartesian(endPoint, stddev);

        segments.push_back(startPoint);
        segments.push_back(endPoint);
    }

    return segments;
}


void writeSphericalToFile(const std::vector<SphericalCoordinates>& coordinates, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    for (const auto& spherical : coordinates) {
        outFile << spherical.theta << ' ' << spherical.phi << '\n';
    }

    outFile.close();
}

void writeSphericalVectorsToFile(const std::vector<SphericalCoordinates>& coordinates, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < coordinates.size(); i += 2) {
        outFile << coordinates[i].theta << " " << coordinates[i].phi << " ";

        outFile << coordinates[i+1].theta << " " << coordinates[i+1].phi << std::endl;
    }

    outFile.close();
}

std::vector<SphericalCoordinates> readSphericalFromFile(const std::string& filename) {
    std::vector<SphericalCoordinates> coordinates;
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return coordinates;
    }

    SphericalCoordinates spherical;
    while (inFile >> spherical.theta >> spherical.phi) {
        coordinates.push_back(spherical);
    }

    inFile.close();
    return coordinates;
}



void writeCartesianToFile(const std::vector<CartesianCoordinates>& coordinates, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    for (const auto& cartesian : coordinates) {
        outFile << cartesian.x << ' ' << cartesian.y << ' ' << cartesian.z << '\n';
    }

    outFile.close();
}

std::vector<SphericalCoordinates> readSphericalVectorsFromFile(const std::string& filename) {
    std::vector<SphericalCoordinates> coordinates;
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return coordinates;
    }

    SphericalCoordinates spherical1, spherical2;
    while (inFile >> spherical1.theta >> spherical1.phi >> spherical2.theta >> spherical2.phi) {
        coordinates.push_back(spherical1);
        coordinates.push_back(spherical2);
    }

    inFile.close();
    return coordinates;
}

void writeCartesianVectorsToFile(const std::vector<CartesianCoordinates>& coordinates, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < coordinates.size(); i += 2) {
        outFile << coordinates[i].x << " " << coordinates[i].y << " " << coordinates[i].z << " ";
        outFile << coordinates[i + 1].x << " " << coordinates[i + 1].y << " " << coordinates[i + 1].z << std::endl;
    }

    outFile.close();
}

std::vector<CartesianCoordinates> readCartesianVectorsFromFile(const std::string& filename) {
    std::vector<CartesianCoordinates> coordinates;
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return coordinates;
    }

    CartesianCoordinates cartesian1, cartesian2;
    while (inFile >> cartesian1.x >> cartesian1.y >> cartesian1.z >> cartesian2.x >> cartesian2.y >> cartesian2.z) {
        coordinates.push_back(cartesian1);
        coordinates.push_back(cartesian2);
    }

    inFile.close();
    return coordinates;
}

std::vector<CartesianCoordinates> readCartesianFromFile(const std::string& filename) {
    std::vector<CartesianCoordinates> coordinates;
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return coordinates;
    }

    CartesianCoordinates cartesian;
    while (inFile >> cartesian.x >> cartesian.y >> cartesian.z) {
        coordinates.push_back(cartesian);
    }

    inFile.close();
    return coordinates;
}

