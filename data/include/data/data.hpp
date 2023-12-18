#pragma once
#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <vector>

/**
 * @brief Class for generating spherical coordinates and working with them.
 */
class SphericalCoordinatesGenerator {
public:
    /**
     * @brief Default constructor.
     */
    SphericalCoordinatesGenerator();

    /**
     * @brief Writes points to a file.
     * @param filename File name to write the points.
     * @param points Vector of vectors representing spherical coordinates of points.
     */
    void writePointsToFile(const std::string &filename, const std::vector<std::vector<double>> &points) const;

    /**
     * @brief Reads points from a file.
     * @param filename File name to read the points.
     * @return Vector of vectors representing spherical coordinates of points.
     */
    std::vector<std::vector<double>> readPointsFromFile(const std::string &filename) const;

    /**
     * @brief Generates points on a spherical arc.
     * @param numPoints Number of points to generate.
     * @param phi_start Starting phi angle in radians.
     * @param theta_start Starting theta angle in radians.
     * @param phi_end Ending phi angle in radians.
     * @param theta_end Ending theta angle in radians.
     * @return Vector of vectors representing the generated spherical coordinates of points.
     */
    std::vector<std::vector<double>> generatePointsOnArc(int numPoints, double phi_start, double theta_start, double phi_end, double theta_end) const;

    /**
     * @brief Adds noise to the spherical coordinates of points on a sphere.
     * @param points Vector of vectors representing spherical coordinates of points.
     * @param noiseLevel The level of noise to add.
     * @return Vector of vectors representing spherical coordinates of noisy points.
     */
    std::vector<std::vector<double>> addCoordinateNoiseOnSphere(const std::vector<std::vector<double>> &points, double noiseLevel) const;

    /**
  * @brief Generates points on the surface of a sphere from a single point, drawing multiple arcs within a specified range.
  *
  * @param numArcs The number of arcs to draw.
  * @param numPointsPerArc The number of points generated on each arc.
  * @param centerPhi Azimuthal angle of the central point.
  * @param centerTheta Polar angle of the central point.
  * @param phi_start Starting limit of the azimuthal angle for generating points on the arc.
  * @param theta_start Starting limit of the polar angle for generating points on the arc.
  * @param phi_end Ending limit of the azimuthal angle for generating points on the arc.
  * @param theta_end Ending limit of the polar angle for generating points on the arc.
  *
  * @return Returns a vector of vectors representing the coordinates of the generated points on the surface of the sphere.
  *         The first index of the outer vector corresponds to the arcs, and the second index of the inner vector corresponds to the coordinates of points (theta, phi).
  */
    std::vector<std::vector<double>> generatePointsFromCenter(int numArcs, int numPointsPerArc, double centerPhi, double centerTheta, double phi_start, double theta_start, double phi_end, double theta_end) const;
};

#endif // DATA_HPP

