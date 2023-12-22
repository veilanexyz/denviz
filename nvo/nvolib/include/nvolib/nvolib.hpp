#pragma once

#ifndef NVOLIB_LIB_HPP
#define NVOLIB_LIB_HPP
#include<iostream>
#include <Eigen/Core>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
class STLCheck {
public:
    static bool isASCII_STL(const std::string& filename);
    static bool isBinary_STL(const std::string& filename);
};


class NVO {
public:
    bool read_triangle_mesh(const std::string& filename);
    void per_vertex_normals();
    void compute_normal_distribution_on_sphere(int num_samples);

private:
    Eigen::MatrixXd V;  
    Eigen::MatrixXi F;  
    Eigen::MatrixXd N;  
    
};

class TextureDrawer {
public:
   // TextureDrawer();
    //~TextureDrawer();
    void loadFromFile(const std::string& filename);
    void drawNormalsAndSaveDrawing(const std::string& txtFilename, const std::string& pngFilename);

private:
    sf::RenderWindow window;
    std::vector<sf::Vector2f> normals;

    
    
    
};

#endif 