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

class Visualization
{
public:
        vtkSmartPointer<vtkActor> generateSphereWithPoints(const std::vector<std::vector<double>>& points, double opacity, double color[3], double radius, double sphereColor[4]) const;
        vtkSmartPointer<vtkActor> createSphere(double radius, double color[3]) const;
        void Mapping(const std::string& imagePath, const std::string& stlPath = "output.stl") const;
};
#endif