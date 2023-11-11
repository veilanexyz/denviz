#include <data/data.hpp>
#include <ctime>

//int main(int argc, char* argv[]) {
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    //if (argc != 4) {
    //    std::cerr << "Usage: " << argv[0] << " <visType> <numObjects> <noiseLevel>" << std::endl;
    //    return 1;
    //}

    //std::string visTypeString = argv[1];
    //std::string numObjectsString = argv[2];
    //std::string noiseLevelString = argv[3];

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
    } else if (visTypeString == "arcs") {
        visType = ARCS;
    } else if (visTypeString == "vectors") {
        visType = VECTORS;
    } else {
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

        for (const auto &point: polarPoints) {
            minRadius = std::min(minRadius, point.radius);
            maxRadius = std::max(maxRadius, point.radius);
            minAngle = std::min(minAngle, point.angle);
            maxAngle = std::max(maxAngle, point.angle);
        }

        double radiusScaleFactor = 400.0 / (maxRadius - minRadius);
        double angleScaleFactor = 2.0 * M_PI / (maxAngle - minAngle);

        for (auto &point: polarPoints) {
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

        }
    }

        //else if (visType == ARCS) {
        //    std::vector<PolarDataPoint> dataWithNoise = generateArcsWithNoise(numObjects, limits, noiseLevel);
        //    writeArcsToFile(dataWithNoise, filename);

        //    std::vector<double> arcData = readArcsFromFile(filename);

        //    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Plot");

        //    while (window.isOpen()) {
        //        sf::Event event;
        //        while (window.pollEvent(event)) {
        //            if (event.type == sf::Event::Closed) {
        //                window.close();
        //            }
        //        }

        //        drawArcs(arcData, window, 1.0);
        //    }

        //}
    else if (visType == VECTORS) {
        std::vector <PolarDataPoint> dataWithNoise = generateDataWithNoise(numObjects, visType, limits, noiseLevel);
        writeVectorsToFile(dataWithNoise, filename);

        std::vector <PolarDataPoint> vectorPoints = readVectorsFromFile(filename);

        double minRadius = std::numeric_limits<double>::max();
        double maxRadius = std::numeric_limits<double>::min();
        double minAngle = std::numeric_limits<double>::max();
        double maxAngle = std::numeric_limits<double>::min();

        for (const auto &point: vectorPoints) {
            minRadius = std::min(minRadius, point.radius);
            maxRadius = std::max(maxRadius, point.radius);
            minAngle = std::min(minAngle, point.angle);
            maxAngle = std::max(maxAngle, point.angle);
        }

        double radiusScaleFactor = 400.0 / (maxRadius - minRadius);
        double angleScaleFactor = 2.0 * M_PI / (maxAngle - minAngle);

        for (auto &point: vectorPoints) {
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
        }

    }
    return 0;
}
