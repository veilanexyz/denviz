#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

enum VisualizationType {
    POINTS,
    ARCS,
    VECTORS
};

struct PolarDataPoint {
    double radius, angle;
};

struct CoordinateLimits {
    double maxRadius;
    double maxAngle;
};

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

void drawPoints(const std::vector<PolarDataPoint>& polarPoints, sf::RenderWindow& window, double scaleFactor) {
    window.clear();

    for (const auto& point : polarPoints) {
        double x = point.radius * std::cos(point.angle) * scaleFactor;
        double y = point.radius * std::sin(point.angle) * scaleFactor;

        sf::CircleShape circle(2.0f);
        circle.setPosition(static_cast<float>(x) + 400.0f, static_cast<float>(y) + 300.0f);

        // Set the color to red
        circle.setFillColor(sf::Color::Red);

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

        lines.append(sf::Vertex(sf::Vector2f(static_cast<float>(x1), static_cast<float>(y1)), sf::Color::Red));
        lines.append(sf::Vertex(sf::Vector2f(static_cast<float>(x2), static_cast<float>(y2)), sf::Color::Red));
    }

    window.draw(lines);
    window.display();
}



//void makeBlackTransparent(sf::Image& image) {
//    image.createMaskFromColor(sf::Color::Black);  // Заменяем черный цвет на прозрачный
//}


void saveToPNG(const sf::RenderWindow& window, const std::string& filename) {
    std::string folderPath = "C:\\test\\";
    std::string fullpath = folderPath + filename;

    sf::Texture texture;
    texture.create(window.getSize().x, window.getSize().y);
    texture.update(window);

    if (texture.copyToImage().saveToFile(fullpath)) {
        std::cout << "Image saved to " << fullpath << std::endl;
    }
    else {
        std::cerr << "Failed to save image to " << fullpath << std::endl;
    }
}

//void makeColorTransparent(sf::Image& image, const sf::Color& color) {
//    for (unsigned int y = 0; y < image.getSize().y; ++y) {
//        for (unsigned int x = 0; x < image.getSize().x; ++x) {
//            if (image.getPixel(x, y) == color) {
//                image.setPixel(x, y, sf::Color::Transparent);
//            }
//        }
//    }
//}


int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <visType> <numObjects> <noiseLevel>" << std::endl;
        return 1;
    }

    std::string visTypeString = argv[1];
    std::string numObjectsString = argv[2];
    std::string noiseLevelString = argv[3];

    std::string visTypeString = "vectors";
    std::string numObjectsString = "500";
    std::string noiseLevelString = "0.3";

    if (!isNumber(numObjectsString)) {
        std::cerr << "Invalid input for numObjects or noiseLevel" << std::endl;
        return 1;
    }

    int numObjects = std::stoi(numObjectsString);

    if (numObjects > 1000000) {
        std::cerr << "Error: numObjects exceeds the maximum allowed value (1000000)" << std::endl;
        return 1;
    }

    double noiseLevel = std::stod(noiseLevelString);

    VisualizationType visType;

    if (visTypeString == "points") {
        visType = POINTS;
    }
    else if (visTypeString == "arcs") {
        visType = ARCS;
    }
    else if (visTypeString == "vectors") {
        visType = VECTORS;
    }
    else {
        std::cerr << "Invalid visualization type" << std::endl;
        return 1;
    }
    CoordinateLimits limits;
    limits.maxRadius = 10.0;
    limits.maxAngle = 2.0 * M_PI;

    std::string typeName = getTypeName(visType);
    std::string filename = typeName + "_data.txt";
    std::vector <PolarDataPoint> dataWithNoise = generateDataWithNoise(numObjects, visType, limits, noiseLevel);

    if (visType == POINTS) {
        std::vector <PolarDataPoint> dataWithNoise = generateDataWithNoise(numObjects, visType, limits, noiseLevel);
        writePointsToFile(dataWithNoise, filename);

        std::vector <PolarDataPoint> polarPoints = readPointsFromFile(filename);
        double minRadius = std::numeric_limits<double>::max();
        double maxRadius = std::numeric_limits<double>::min();
        double minAngle = std::numeric_limits<double>::max();
        double maxAngle = std::numeric_limits<double>::min();

        for (const auto& point : polarPoints) {
            minRadius = std::min(minRadius, point.radius);
            maxRadius = std::max(maxRadius, point.radius);
            minAngle = std::min(minAngle, point.angle);
            maxAngle = std::max(maxAngle, point.angle);
        }

        double radiusScaleFactor = 400.0 / (maxRadius - minRadius);
        double angleScaleFactor = 2.0 * M_PI / (maxAngle - minAngle);

        for (auto& point : polarPoints) {
            point.radius = (point.radius - minRadius) * radiusScaleFactor;
            point.angle = (point.angle - minAngle) * angleScaleFactor;
        }

        sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Plot");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            drawPoints(polarPoints, window, 1.0);
            saveToPNG(window, "data.png");
        }
        //sf::Image textureImage;
        //if (!textureImage.loadFromFile("data.png")) {
        //    return -1; // Failed to load texture
        //}

        //// Make black color transparent
        //sf::Color blackColor(0, 0, 0);
        //makeColorTransparent(textureImage, blackColor);
    }

    //else if (visType == ARCS) {

    //}

    else if (visType == VECTORS) {
        std::vector <PolarDataPoint> dataWithNoise = generateDataWithNoise(numObjects, visType, limits, noiseLevel);
        writeVectorsToFile(dataWithNoise, filename);

        std::vector <PolarDataPoint> vectorPoints = readVectorsFromFile(filename);

        double minRadius = std::numeric_limits<double>::max();
        double maxRadius = std::numeric_limits<double>::min();
        double minAngle = std::numeric_limits<double>::max();
        double maxAngle = std::numeric_limits<double>::min();
        for (const auto& point : vectorPoints) {
            minRadius = std::min(minRadius, point.radius);
            maxRadius = std::max(maxRadius, point.radius);
            minAngle = std::min(minAngle, point.angle);
            maxAngle = std::max(maxAngle, point.angle);
        }

        double radiusScaleFactor = 400.0 / (maxRadius - minRadius);
        double angleScaleFactor = 2.0 * M_PI / (maxAngle - minAngle);

        for (auto& point : vectorPoints) {
            point.radius = (point.radius - minRadius) * radiusScaleFactor;
            point.angle = (point.angle - minAngle) * angleScaleFactor;
        }

        sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Plot");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            drawVectors(vectorPoints, window, 1.0);
            saveToPNG(window, "data.png");

        }
        //sf::Image textureImage;
        //if (!textureImage.loadFromFile("data.png")) {
        //    return -1; // Failed to load texture
        //}

        //// Make black color transparent
        //sf::Color blackColor(0, 0, 0);
        //makeColorTransparent(textureImage, blackColor);
    }
    return 0;
}







