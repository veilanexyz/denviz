#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>

struct Point {
    double x, y, z;

    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    // Custom equality operator for Point
    bool operator==(const Point& other) const {
        double epsilon = 1e-6;
        return (std::abs(x - other.x) < epsilon &&
                std::abs(y - other.y) < epsilon &&
                std::abs(z - other.z) < epsilon);
    }

    // Custom comparison operator for using Point as keys in std::map
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return z < other.z;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

};

struct Triangle {
    Point p1, p2, p3;

    Triangle(const Point& p1, const Point& p2, const Point& p3) : p1(p1), p2(p2), p3(p3) {}

    // Custom equality operator for Triangle
    bool operator==(const Triangle& other) const {
        return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3);
    }

    // Custom comparison operator for using Triangle as keys in std::map
    bool operator<(const Triangle& other) const {
        if (p1 != other.p1) return p1 < other.p1;
        if (p2 != other.p2) return p2 < other.p2;
        return p3 < other.p3;
    }
};

struct Graph {
    std::map<Triangle, int> triangleToIndex;
    std::vector<Triangle> triangles;
    std::vector<std::set<int>> adjacencyList;

    int addTriangle(const Triangle& triangle) {
        if (triangleToIndex.find(triangle) == triangleToIndex.end()) {
            int newIndex = triangles.size();
            triangles.push_back(triangle);
            triangleToIndex[triangle] = newIndex;
            adjacencyList.push_back(std::set<int>());
            return newIndex;
        } else {
            return triangleToIndex[triangle];
        }
    }

    void addEdge(int triangleIndex1, int triangleIndex2) {
        adjacencyList[triangleIndex1].insert(triangleIndex2);
        adjacencyList[triangleIndex2].insert(triangleIndex1);
    }
};
Point getMidpoint(const Point& p1, const Point& p2) {
    double x = (p1.x + p2.x) / 2;
    double y = (p1.y + p2.y) / 2;
    double z = (p1.z + p2.z) / 2;
    return Point(x, y, z);
}

std::vector<Point> divideTriangle(const Point& p1, const Point& p2, const Point& p3, int depth, Graph& graph) {
    std::vector<Point> points;
    if (depth == 0) {
        points.push_back(p1);
        points.push_back(p2);
        points.push_back(p3);
    } else {
        Point mid1 = getMidpoint(p1, p2);
        Point mid2 = getMidpoint(p2, p3);
        Point mid3 = getMidpoint(p1, p3);

        int mid1Idx = graph.addTriangle(Triangle(p1, mid1, mid3));
        int mid2Idx = graph.addTriangle(Triangle(mid1, p2, mid2));
        int mid3Idx = graph.addTriangle(Triangle(mid3, mid2, p3));

        points = divideTriangle(p1, mid1, mid3, depth - 1, graph);
        points.insert(points.end(), divideTriangle(mid1, p2, mid2, depth - 1, graph).begin(), divideTriangle(mid1, p2, mid2, depth - 1, graph).end());
        points.insert(points.end(), divideTriangle(mid3, mid2, p3, depth - 1, graph).begin(), divideTriangle(mid3, mid2, p3, depth - 1, graph).end());

        graph.addEdge(mid1Idx, mid2Idx);
        graph.addEdge(mid2Idx, mid3Idx);
        graph.addEdge(mid3Idx, mid1Idx);
    }
    return points;
}


int main() {
    // вершины икосаэдра на сфере
    std::vector<Point> vertices = {
            Point(1, 0, 0),
            Point(1, 0, M_PI / 3),
            Point(1, 0, 2 * M_PI / 3),
            Point(1, 0, M_PI),
            Point(1, 0, 4 * M_PI / 3),
            Point(1, 0, 5 * M_PI / 3),
            Point(1, M_PI / 3, M_PI / 6),
            Point(1, M_PI / 3, 5 * M_PI / 6),
            Point(1, 2 * M_PI / 3, M_PI / 6),
            Point(1, 2 * M_PI / 3, 5 * M_PI / 6),
            Point(1, 4 * M_PI / 3, M_PI / 6),
            Point(1, 4 * M_PI / 3, 5 * M_PI / 6)
    };

    // Список индексов вершин для каждого исходного треугольника
    std::vector<std::vector<int>> triangles = {
            {0, 1, 6},
            {0, 6, 2},
            {0, 2, 7},
            {0, 7, 3},
            {0, 3, 8},
            {0, 8, 4},
            {0, 4, 9},
            {0, 9, 5},
            {0, 5, 10},
            {0, 10, 1},
            {1, 6, 11},
            {1, 11, 2},
            {2, 7, 6},
            {2, 11, 3},
            {3, 7, 8},
            {3, 11, 4},
            {4, 9, 8},
            {4, 11, 5},
            {5, 10, 9},
            {5, 11, 10}
    };

    int depth = 4;

    // Из каждого исходного треугольника создаем граф
    Graph graph;
    for (const auto& triangleIndices : triangles) {
        const Point& p1 = vertices[triangleIndices[0]];
        const Point& p2 = vertices[triangleIndices[1]];
        const Point& p3 = vertices[triangleIndices[2]];

        divideTriangle(p1, p2, p3, depth, graph);
    }

    // Выводим информацию о треугольниках
    for (int i = 0; i < graph.triangles.size(); i++) {
        std::cout << "Triangle " << i + 1 << ": ";
        const Triangle& triangle = graph.triangles[i];
        std::cout << "(" << triangle.p1.x << ", " << triangle.p1.y << ", " << triangle.p1.z << ") - ";
        std::cout << "(" << triangle.p2.x << ", " << triangle.p2.y << ", " << triangle.p2.z << ") - ";
        std::cout << "(" << triangle.p3.x << ", " << triangle.p3.y << ", " << triangle.p3.z << ")\n";
    }

    // Выводим информацию о связях между треугольниками
    for (int i = 0; i < graph.adjacencyList.size(); i++) {
        std::cout << "Adjacent triangles to Triangle " << i + 1 << ": ";
        for (int neighbor : graph.adjacencyList[i]) {
            std::cout << neighbor + 1 << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}


