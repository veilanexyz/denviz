#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkTriangle.h>
#include <vtkPolyData.h>
#include <vtkXMLPolyDataWriter.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#define PI 3.14

struct Point {
    double x, y, z;
    Point(double x, double y, double z) : x(x), y(y), z(z) {}

    bool operator==(const Point& other) const {
        double epsilon = 1e-6;
        return (std::abs(x - other.x) < epsilon &&
                std::abs(y - other.y) < epsilon &&
                std::abs(z - other.z) < epsilon);
    }

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

    bool operator==(const Triangle& other) const {
        return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3);
    }

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
    std::vector<Point> vertices = {
        Point(1, 0, 0),
        Point(1, 0, PI / 3),
        Point(1, 0, 2 * PI / 3),
        Point(1, 0, PI),
        Point(1, 0, 4 * PI/ 3),
        Point(1, 0, 5 * PI / 3),
        Point(1, PI / 3, PI / 6),
        Point(1, PI / 3, 5 * PI / 6),
        Point(1, 2 * PI / 3, PI/ 6),
        Point(1, 2 * PI / 3, 5 * PI / 6),
        Point(1, 4 * PI / 3, PI / 6),
        Point(1, 4 * PI / 3, 5 * PI / 6)
    };

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

    vtkSmartPointer<vtkPoints> vtkPoints = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vtkTriangles = vtkSmartPointer<vtkCellArray>::New();

    for (const auto& triangleIndices : triangles) {
        const Point& p1 = vertices[triangleIndices[0]];
        const Point& p2 = vertices[triangleIndices[1]];
        const Point& p3 = vertices[triangleIndices[2]];

        std::vector<Point> points = divideTriangle(p1, p2, p3, depth, graph);

        for (const Point& point : points) {
            vtkPoints->InsertNextPoint(point.x, point.y, point.z);
        }

        vtkSmartPointer<vtkTriangle> vtkTriangle = vtkSmartPointer<vtkTriangle>::New();
        vtkTriangle->GetPointIds()->SetId(0, vtkPoints->GetNumberOfPoints() - 3);
        vtkTriangle->GetPointIds()->SetId(1, vtkPoints->GetNumberOfPoints() - 2);
        vtkTriangle->GetPointIds()->SetId(2, vtkPoints->GetNumberOfPoints() - 1);

        vtkTriangles->InsertNextCell(vtkTriangle);
    }

    vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(vtkPoints);
    polyData->SetPolys(vtkTriangles);

    vtkSmartPointer<vtkXMLPolyDataWriter> writer = vtkSmartPointer<vtkXMLPolyDataWriter>::New();
    writer->SetFileName("output.vtp");
    writer->SetInputData(polyData);
    writer->Write();

    return 0;
}
