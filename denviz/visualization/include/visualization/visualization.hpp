#pragma once
#ifndef VISUALIZATION_HPP
#define VISUALIZATION_HPP

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vector>
#include "data/data.hpp"

/**
 * @brief Class for creating and manipulating 3D visualizations using VTK.
 */
class Visualization
{
public:
    /**
     * @brief Generates a VTK actor representing a sphere with specified points.
     *
     * @param points Vector of points in spherical coordinates.
     * @param opacity Opacity of the sphere.
     * @param color RGB color of the sphere.
     * @param radius Radius of the sphere.
     * @return VTK actor representing the sphere with points.
     */
    vtkSmartPointer<vtkActor> generateSphereWithPoints(const std::vector<Point>& points, double opacity, double color[3], double radius) const;

    /**
     * @brief Creates a VTK actor representing a simple colored sphere.
     *
     * @param radius Radius of the sphere.
     * @param color RGB color of the sphere.
     * @return VTK actor representing the colored sphere.
     */
    vtkSmartPointer<vtkActor> createSphere(double radius, double color[3]) const;

    /**
     * @brief Creates a VTK actor representing a real-looking sphere with texture mapping.
     *
     * @param radius Radius of the sphere.
     * @param color RGB color of the sphere.
     * @param opacity Opacity of the sphere.
     * @return VTK actor representing the real-looking sphere.
     */
    vtkSmartPointer<vtkActor> createRealSphere(double radius, double color[3], double opacity) const;

    /**
     * @brief Creates a VTK actor representing a sphere with a texture mapped from an image file.
     *
     * @param imagePath Path to the PNG image file used for texture mapping.
     * @param radius Radius of the sphere.
     * @param color RGB color of the sphere.
     * @param opacity Opacity of the sphere.
     * @return VTK actor representing the sphere with texture mapping.
     */
    vtkSmartPointer<vtkActor> Mapping(const std::string& imagePath, double radius, const double color[3], double opacity) const;
};

#endif
