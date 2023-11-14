#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <random>
#include <filesystem>
#include <SFML/Graphics.hpp>

struct Arc {
    double azim, inclin;
};

struct Vector {
    double x, y;
};

struct Point {
    double x, y;
};

double randomRange(double min, double max) {
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) / (max - min));
}
template <typename Container>
void drawArcs(sf::RenderWindow& window, const Container& arcs, int numData) {
    for (const auto& arc : arcs) {
        sf::VertexArray arcVertices(sf::LinesStrip, numData);


        for (int i = 0; i < numData; ++i) {
            float angle = arc.azim + i * (2 * std::acos(-1.0)) / (100 - 1);
            float x = static_cast<float>(std::cos(angle) * numData * 10);
            float y = static_cast<float>(std::sin(arc.inclin) * numData * 10);
            arcVertices[i] = sf::Vertex(sf::Vector2f(200 + x, 200 + y));
        }

        window.draw(arcVertices);
    }

    window.display();
}
template <typename Container>
void drawPoints(sf::RenderWindow& window, const Container& data, int numData) {
    

        for (const auto& point : data) {
            sf::CircleShape pointShape(1);
            pointShape.setFillColor(sf::Color::Red);
            pointShape.setPosition(point.x * 400, point.y * 400);
            window.draw(pointShape);
        }

        window.display();
    }
template <typename Container>
void drawVectors(sf::RenderWindow& window, const Container&data, int numData) {
   

       for (const auto& vector : data) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(400, 400)),
                sf::Vertex(sf::Vector2f((vector.x + 1) * 400, (vector.y + 1) * 400))
            };

            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }


void generateDataAndDraw(const std::string& dataType, const std::string& containerType, int numData, const std::string& folderPath ) {
    if (!std::filesystem::exists(folderPath)) {
        std::filesystem::create_directory(folderPath);
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    if (dataType == "arcs") {

        sf::RenderWindow window(sf::VideoMode(400, 400), "Отображение дуг");
        window.clear();
        if (containerType == "vector") {
            std::vector<Arc> dataVector;
            for (int i = 0; i < numData; ++i) {
                double azim = randomRange(0.0, 2.0 * std::acos(-1.0));
                double inclin = randomRange(0.0, std::asin(-1.0));
                dataVector.emplace_back(Arc{ azim, inclin });
                drawArcs(window, dataVector, numData);
            }

            std::ofstream arcsVectorFile(folderPath + "/arcsVector.txt");
            for (const auto& arc : dataVector) {
                arcsVectorFile << "(" << arc.azim << ", " << arc.inclin << ")" << std::endl;
            }
            arcsVectorFile.close();
        }
        else if (containerType == "list") {
            std::list<Arc> dataList;
            for (int i = 0; i < numData; ++i) {
                double azim = randomRange(0.0, 2.0 * std::acos(-1.0));
                double inclin = randomRange(0.0, std::asin(-1.0));
                dataList.emplace_back(Arc{ azim, inclin });
                drawArcs(window, dataList, numData);
            }

            std::ofstream arcsListFile(folderPath + "/arcsList.txt");
            for (const auto& arc : dataList) {
                arcsListFile << "(" << arc.azim << ", " << arc.inclin << ")" << std::endl;
            }
            arcsListFile.close();
        }
        else if (containerType == "deque") {
            std::deque<Arc> dataDeque;
            for (int i = 0; i < numData; ++i) {
                double azim = randomRange(0.0, 2.0 * std::acos(-1.0));
                double inclin = randomRange(0.0, std::asin(-1.0));
                dataDeque.emplace_back(Arc{ azim, inclin });
                drawArcs(window, dataDeque, numData);
            }

            std::ofstream arcsDequeFile(folderPath + "/arcsDeque.txt");
            for (const auto& arc : dataDeque) {
                arcsDequeFile << "(" << arc.azim << ", " << arc.inclin << ")" << std::endl;
            }
            arcsDequeFile.close();
        }
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
    }
    else if (dataType == "vectors") {
        sf::RenderWindow window(sf::VideoMode(800, 800), "Отображение векторов");
        if (containerType == "vector") {
            std::vector<Vector> dataVector;
            for (int i = 0; i < numData; ++i) {
                double x = randomRange(0.0, 2*std::acos(-1.0));
                double y = randomRange(0.0, std::acos(-1.0));
                dataVector.emplace_back(Vector{ x, y });
                drawVectors(window, dataVector, numData);

            }

            std::ofstream vectorsVectorFile(folderPath + "/vectorsVector.txt");
            for (const auto& vec : dataVector) {
                vectorsVectorFile << "(" << vec.x << " " << vec.y << ")" << std::endl;
            }
            vectorsVectorFile.close();
        }
        else if (containerType == "list") {
            std::list<Vector> dataList;
            for (int i = 0; i < numData; ++i) {
                double x = randomRange(0.0, 2 * std::acos(-1.0));
                double y = randomRange(0.0, std::acos(-1.0));
                dataList.emplace_back(Vector{ x, y });
                drawVectors(window, dataList, numData);
            }

            std::ofstream vectorsListFile(folderPath + "/vectorsList.txt");
            for (const auto& vec : dataList) {
                vectorsListFile << "(" << vec.x << " " << vec.y << ")" << std::endl;
            }
            vectorsListFile.close();
        }
        else if (containerType == "deque") {
            std::deque<Vector> dataDeque;
            for (int i = 0; i < numData; ++i) {
                double x = randomRange(0.0, 2 * std::acos(-1.0));
                double y = randomRange(0.0, std::acos(-1.0));
                dataDeque.emplace_back(Vector{ x, y });
                drawVectors(window, dataDeque, numData);
            }

            std::ofstream vectorsDequeFile(folderPath + "/vectorsDeque.txt");
            for (const auto& vec : dataDeque) {
                vectorsDequeFile << "(" << vec.x << " " << vec.y << ")" << std::endl;
            }
            vectorsDequeFile.close();
        }
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear();
        }
    }
    else if (dataType == "points") {

        sf::RenderWindow window(sf::VideoMode(800, 800), "Отображение точек");
        window.clear();
        if (containerType == "vector") {
            std::vector<Point> dataVector;
            for (int i = 0; i < numData; ++i) {
                double x = randomRange(std::asin(-1.0), std::asin(1.0));
                double y = randomRange(std::acos(-1.0), std::acos(1.0));
                dataVector.emplace_back(Point{ x, y });
                drawPoints(window, dataVector,numData);
            }

            std::ofstream pointsVectorFile(folderPath + "/pointsVector.txt");
            for (const auto& point : dataVector) {
                pointsVectorFile << "(" << point.x << " " << point.y << ")" << std::endl;
            }
            pointsVectorFile.close();
        }
        else if (containerType == "list") {
            std::list<Point> dataList;
            for (int i = 0; i < numData; ++i) {
                double x = randomRange(std::asin(-1.0), std::asin(1.0));
                double y = randomRange(std::acos(-1.0), std::acos(1.0));
                dataList.emplace_back(Point{ x, y });
                drawPoints(window, dataList,numData);
            }

            std::ofstream pointsListFile(folderPath + "/pointsList.txt");
            for (const auto& point : dataList) {
                pointsListFile << "(" << point.x << " " << point.y << ")" << std::endl;
            }
            pointsListFile.close();
        }
        else if (containerType == "deque") {
            std::deque<Point> dataDeque;
            for (int i = 0; i < numData; ++i) {
                double x = randomRange(std::asin(-1.0), std::asin(1.0));
                double y = randomRange(std::acos(-1.0), std::acos(1.0));
                dataDeque.emplace_back(Point{ x, y });
                drawPoints(window, dataDeque, numData);
            } 

            std::ofstream pointsDequeFile(folderPath + "/pointsDeque.txt");
            for (const auto& point : dataDeque) {
                pointsDequeFile << "(" << point.x << " " << point.y << ")" << std::endl;
            }
            pointsDequeFile.close();
        }
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
    }

}

int main() {
    std::setlocale(LC_ALL, "Russian");

    std::string dataType;
    std::string containerType;
    int numData;

    std::cout << "Введите тип данных (arcs, vectors, points): ";
    std::cin >> dataType;

    std::cout << "Введите тип контейнера (vector, list, deque): ";
    std::cin >> containerType;

    std::cout << "Введите количество данных: ";
    std::cin >> numData;

    std::string folderPath = "data";

    generateDataAndDraw(dataType, containerType, numData, folderPath);

    std::cout << "Данные успешно сгенерированы и сохранены в папку data." << std::endl;

    return 0;
}
