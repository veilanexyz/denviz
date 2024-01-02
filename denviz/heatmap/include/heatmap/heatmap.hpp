#pragma once
#ifndef HEATMAP_HPP
#define HEATMAP_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#define M_PI 3.14

struct XYPoint {
	double x;
	double y;

	XYPoint(double x, double y) : x(x), y(y) {}
};

class HeatMap {
	public:
		std::vector<XYPoint> readPointsFromFile(const std::string& filename) const;
		void Heatmap(const std::string& filename) const;
	private:
		sf::RenderWindow window;
};

#endif