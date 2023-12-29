#pragma once
#ifndef DATA_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#define M_PI 3.14

struct Point {
	double x;
	double y;

	Point(double x, double y) : x(x), y(y) {}
};

class Texture {
	public:
		std::vector<Point> readPointsFromFile(const std::string& filename) const;
		void Heatmap(const std::string& filename) const;
	private:
		sf::RenderWindow window;
};

#endif