#include <data/data.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string getTypeName(VisualizationType visType) {
    switch (visType) {
        case POINTS:
            return "points";
        case ARCS:
            return "arcs";
        case VECTORS:
            return "vectors";
        default:
            return "unknown";
    }
}

std::vector<PolarDataPoint> generatePointsWithNoise(int numPoints, const CoordinateLimits& limits, double noiseLevel) {
    std::vector<PolarDataPoint> data;

    for (int i = 0; i < numPoints; ++i) {
        PolarDataPoint point;
        point.radius = static_cast<double>(rand()) / RAND_MAX * limits.maxRadius;
        point.angle = static_cast<double>(rand()) / RAND_MAX * limits.maxAngle;

        point.radius += noiseLevel * static_cast<double>(rand()) / RAND_MAX;
        point.angle += noiseLevel * static_cast<double>(rand()) / RAND_MAX;

        data.push_back(point);
    }

    return data;
}

std::vector<PolarDataPoint> generateArcsWithNoise(int numArcs, const CoordinateLimits& limits, double noiseLevel) {
    std::vector<PolarDataPoint> data;

    for (int i = 0; i < numArcs; ++i) {
        PolarDataPoint center;
        center.radius = static_cast<double>(rand()) / RAND_MAX * limits.maxRadius;
        center.angle = static_cast<double>(rand()) / RAND_MAX * limits.maxAngle;

        double radius = static_cast<double>(rand()) / RAND_MAX * limits.maxRadius;
        double startAngle = static_cast<double>(rand()) / RAND_MAX * limits.maxAngle;
        double endAngle = static_cast<double>(rand()) / RAND_MAX * limits.maxAngle;

        if (startAngle > endAngle) {
            std::swap(startAngle, endAngle);
        }

        for (double angle = startAngle; angle <= endAngle; angle += 0.01) {
            PolarDataPoint point;
            point.radius = radius;
            point.angle = center.angle + angle;
            point.radius += noiseLevel * static_cast<double>(rand()) / RAND_MAX;
            point.angle += noiseLevel * static_cast<double>(rand()) / RAND_MAX;
            data.push_back(point);
        }
    }

    return data;
}



std::vector<PolarDataPoint> generateVectorsWithNoise(int numVectors, const CoordinateLimits& limits, double noiseLevel) {
    std::vector<PolarDataPoint> data;

    for (int i = 0; i < numVectors; ++i) {
        PolarDataPoint point;
        point.radius = static_cast<double>(rand()) / RAND_MAX * limits.maxRadius;
        point.angle = static_cast<double>(rand()) / RAND_MAX * limits.maxAngle;

        point.radius += noiseLevel * static_cast<double>(rand()) / RAND_MAX;
        point.angle += noiseLevel * static_cast<double>(rand()) / RAND_MAX;

        data.push_back(point);
    }

    return data;
}

std::vector<PolarDataPoint> generateDataWithNoise(int numObjects, VisualizationType visType, const CoordinateLimits& limits, double noiseLevel) {
    if (visType == POINTS) {
        return generatePointsWithNoise(numObjects, limits, noiseLevel);
    }
    else if (visType == ARCS) {
        return generateArcsWithNoise(numObjects, limits, noiseLevel);
    }
    else if (visType == VECTORS) {
        return generateVectorsWithNoise(numObjects, limits, noiseLevel);
    }
    else {
        std::cerr << "Invalid visualization type" << std::endl;
        return {};
    }
}


bool isNumber(const std::string& str) {
    std::istringstream iss(str);
    double dummy;
    return static_cast<bool>(iss >> dummy);
}


void writeVectorsToFile(const std::vector<PolarDataPoint>& data, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        file << std::fixed << std::setprecision(2);

        for (size_t i = 0; i < data.size(); i += 2) {
            file << data[i].radius << " " << data[i].angle << " ";

            file << data[i + 1].radius << " " << data[i + 1].angle << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

std::vector<PolarDataPoint> readVectorsFromFile(const std::string& filename) {
    std::vector<PolarDataPoint> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return data;
    }

    double startRadius, startAngle, endRadius, endAngle;
    while (file >> startRadius >> startAngle >> endRadius >> endAngle) {
        data.push_back({ startRadius, startAngle });
        data.push_back({ endRadius, endAngle });
    }

    file.close();
    return data;
}


void writePointsToFile(const std::vector<PolarDataPoint>& data, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        file << std::fixed << std::setprecision(2);

        for (const auto& point : data) {
            file << point.radius << " " << point.angle << std::endl;
        }

        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

std::vector<PolarDataPoint> readPointsFromFile(const std::string& filename) {
    std::vector<PolarDataPoint> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return data;
    }

    double radius, angle;
    while (file >> radius >> angle) {
        data.push_back({ radius, angle });
    }

    file.close();
    return data;
}


void writeArcsToFile(const std::vector<double>& data, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        file << std::fixed << std::setprecision(2);

        for (size_t i = 0; i < data.size(); i += 5) {
            file << data[i] << " " << data[i + 1] << " "
                 << data[i + 2] << " " << data[i + 3] << " " << data[i + 4] << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

std::vector<double> readArcsFromFile(const std::string& filename) {
    std::vector<double> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return data;
    }

    double value;
    while (file >> value) {
        data.push_back(value);
    }

    file.close();
    return data;
}


void drawPoints(const std::vector<PolarDataPoint>& polarPoints, sf::RenderWindow& window, double scaleFactor) {
    window.clear();

    for (const auto& point : polarPoints) {
        double x = point.radius * std::cos(point.angle) * scaleFactor;
        double y = point.radius * std::sin(point.angle) * scaleFactor;


        sf::CircleShape circle(2.0f);
        circle.setPosition(static_cast<float>(x) + 400.0f, static_cast<float>(y) + 300.0f);
        window.draw(circle);
    }

    window.display();
}


void drawVectors(const std::vector<PolarDataPoint>& polarPoints, sf::RenderWindow& window, double scaleFactor) {
    window.clear();

    sf::VertexArray lines(sf::Lines);

    for (size_t i = 0; i + 1 < polarPoints.size(); i += 2) {
        double x1 = polarPoints[i].radius * std::cos(polarPoints[i].angle) * scaleFactor + 400.0;
        double y1 = polarPoints[i].radius * std::sin(polarPoints[i].angle) * scaleFactor + 300.0;

        double x2 = polarPoints[i + 1].radius * std::cos(polarPoints[i + 1].angle) * scaleFactor + 400.0;
        double y2 = polarPoints[i + 1].radius * std::sin(polarPoints[i + 1].angle) * scaleFactor + 300.0;

        lines.append(sf::Vertex(sf::Vector2f(static_cast<float>(x1), static_cast<float>(y1))));
        lines.append(sf::Vertex(sf::Vector2f(static_cast<float>(x2), static_cast<float>(y2))));
    }

    window.draw(lines);
    window.display();
}

void drawArcs(const std::vector<double>& arcData, sf::RenderWindow& window, double scaleFactor) {
    window.clear();

    sf::VertexArray lines(sf::Lines);

    for (size_t i = 0; i < arcData.size(); i += 5) {
        double centerX = arcData[i];
        double centerY = arcData[i + 1];
        double radius = arcData[i + 2];
        double startAngle = arcData[i + 3];
        double endAngle = arcData[i + 4];

        for (double angle = startAngle; angle <= endAngle; angle += 0.01) {
            double x1 = centerX + radius * std::cos(angle) * scaleFactor + 400.0;
            double y1 = centerY + radius * std::sin(angle) * scaleFactor + 300.0;

            double x2 = centerX + radius * std::cos(angle + 0.01) * scaleFactor + 400.0;
            double y2 = centerY + radius * std::sin(angle + 0.01) * scaleFactor + 300.0;

            lines.append(sf::Vertex(sf::Vector2f(x1, y1)));
            lines.append(sf::Vertex(sf::Vector2f(x2, y2)));
        }
    }

    window.draw(lines);
    window.display();
}

void saveToPNG(const sf::RenderWindow& window, const std::string& filename) {
    // Capture the content of the window
    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);

    // Create an image from the texture
    sf::Image image = texture.copyToImage();

    // Save the image to a file
    if (image.saveToFile(filename)) {
        std::cout << "Image saved to " << filename << std::endl;
    }
    else {
        std::cerr << "Failed to save image to " << filename << std::endl;
    }
}
