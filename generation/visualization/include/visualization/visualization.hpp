#pragma once
#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vector>
#include "data/data.hpp"

class Visualization
{
public:

    vtkSmartPointer<vtkActor> generateSphereWithPoints(const std::vector<Point>& points, double opacity, double color[3], double radius) const;

    vtkSmartPointer<vtkActor> createSphere(double radius, double color[3]) const;

    vtkSmartPointer<vtkActor> createRealSphere(double radius, double color[3], double opacity) const;

    vtkSmartPointer<vtkActor> Mapping(const std::string& imagePath, double radius, const double color[3], double opacity) const;
};

#endif
