#pragma once
#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPointData.h>
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>
#include <vtkTexture.h>
#include <vtkFloatArray.h>
#include <vtkPNGReader.h>
#include <vtkPNGWriter.h>
#include <vtkCamera.h>
#include <vtkWindowToImageFilter.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>
#include <iostream>
#include <vector>
#include <vtkWindowToImageFilter.h>
#include "data/data.hpp"

class Visualization
{
public:
        vtkSmartPointer<vtkActor> generateSphereWithPoints(const std::vector<Point>& points, double opacity, double color[3], double radius ) const;
        vtkSmartPointer<vtkActor> createRealSphere(double radius, double color[3], double opacity) const;
        vtkSmartPointer<vtkActor> createSphere(double radius, double color[3]) const;
        vtkSmartPointer<vtkActor> Mapping(const std::string& imagePath, double radius, const double color[3], double opacity) const;
};
#endif
