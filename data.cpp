#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <random>
#include <filesystem>

struct Arc {
    double azim, inclin;
};

double randomRange(double min, double max) {
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) / (max - min));
}

void generateData(int numArc, const std::string& folderPath) {
    if (!std::filesystem::exists(folderPath)) {
        std::filesystem::create_directory(folderPath);
    }

    std::vector<Arc> arcsVector;
    std::list<Arc> arcsList;
    std::deque<Arc> arcsDeque;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < numArc; ++i) {
        double azim = randomRange(0.0, 2.0 * std::acos(-1.0));
        double inclin = randomRange(0.0, std::asin(-1.0));

        Arc arc{ azim, inclin };
        arcsVector.emplace_back(arc);
        arcsList.emplace_back(arc);
        arcsDeque.emplace_back(arc);
    }

    std::ofstream arcsVectorFile(folderPath + "/arcsVector.txt");
    for (const auto& arc : arcsVector) {
        arcsVectorFile << "(" << arc.azim << ", " << arc.inclin << ")" << std::endl;
    }
    arcsVectorFile.close();

    std::ofstream arcsListFile(folderPath + "/arcsList.txt");
    for (const auto& arc : arcsList) {
        arcsListFile << "(" << arc.azim << ", " << arc.inclin << ")" << std::endl;
    }
    arcsListFile.close();

    std::ofstream arcsDequeFile(folderPath + "/arcsDeque.txt");
    for (const auto& arc : arcsDeque) {
        arcsDequeFile << "(" << arc.azim << ", " << arc.inclin << ")" << std::endl;
    }
    arcsDequeFile.close();
}

struct Vector {
    double x, y;
};

double randomRange_1() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(0.0, 1.0);
    return dis(gen);
}

void generateData_1(int numVec, const std::string& folderPath) {
    if (!std::filesystem::exists(folderPath)) {
        std::filesystem::create_directory(folderPath);
    }

    std::vector<Vector> vectorsVector;
    std::list<Vector> vectorsList;
    std::deque<Vector> vectorsDeque;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < numVec; ++i) {
        double x = randomRange_1();
        double y = randomRange_1();

        Vector vector{ x, y };
        vectorsVector.emplace_back(vector);
        vectorsList.emplace_back(vector);
        vectorsDeque.emplace_back(vector);
    }

    std::ofstream vectorsVectorFile(folderPath + "/vectorsVector.txt");
    for (const auto& vec : vectorsVector) {
        vectorsVectorFile << "(" << vec.x << " " << vec.y << ")" << std::endl;
    }
    vectorsVectorFile.close();

    std::ofstream vectorsListFile(folderPath + "/vectorsList.txt");
    for (const auto& vec : vectorsList) {
        vectorsListFile << "(" << vec.x << " " << vec.y << ")" << std::endl;
    }
    vectorsListFile.close();

    std::ofstream vectorsDequeFile(folderPath + "/vectorsDeque.txt");
    for (const auto& vec : vectorsDeque) {
        vectorsDequeFile << "(" << vec.x << " " << vec.y << ")" << std::endl;
    }
    vectorsDequeFile.close();
}

struct Point {
    double x, y;
};

Point generatePoint() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> disX(0.0, 1.0);
    std::uniform_real_distribution<double> disY(0.0, 1.0);

    double x = disX(gen);
    double y = disY(gen);

    return { x, y };
}

void generateData_2(int numPoint, const std::string& folderPath) {
    if (!std::filesystem::exists(folderPath)) {
        std::filesystem::create_directory(folderPath);
    }

    std::vector<Point> pointsVector;
    std::list<Point> pointsList;
    std::deque<Point> pointsDeque;

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < numPoint; ++i) {
        Point point = generatePoint();
        pointsVector.emplace_back(point);
        pointsList.emplace_back(point);
        pointsDeque.emplace_back(point);
    }std::ofstream pointsVectorFile(folderPath + "/pointsVector.txt");
    for (const auto& point : pointsVector) {
        pointsVectorFile << "(" << point.x << " " << point.y << ")" << std::endl;
    }
    pointsVectorFile.close();

    std::ofstream pointsListFile(folderPath + "/pointsList.txt");
    for (const auto& point : pointsList) {
        pointsListFile << "(" << point.x << " " << point.y << ")" << std::endl;
    }
    pointsListFile.close();

    std::ofstream pointsDequeFile(folderPath + "/pointsDeque.txt");
    for (const auto& point : pointsDeque) {
        pointsDequeFile << "(" << point.x << " " << point.y << ")" << std::endl;
    }
    pointsDequeFile.close();
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    int numArc, numVec, numPoint;
    std::cout << "Введите значение дуг: ";
    std::cin >> numArc;
    std::cout << "Введите значение векторов: ";
    std::cin >> numVec;
    std::cout << "Введите значения точек: ";
    std::cin >> numPoint;
    std::string folderPath = "data";

    generateData(numArc, folderPath);
    generateData_1(numVec, folderPath);
    generateData_2(numPoint, folderPath);
    std::cout << "Данные успешно сгенерированы и сохранены в папку data." << std::endl;

    return 0;
}

