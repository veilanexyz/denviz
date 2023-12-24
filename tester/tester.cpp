#include<nvolib/nvolib.hpp>
#include <igl/read_triangle_mesh.h>
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " path to stl file" << std::endl;
        return 1;
    }

    std::string mesh_file_path = argv[1];
   

    if (STLCheck::isASCII_STL(mesh_file_path)) {
        std::cout << "The file is in ASCII STL format and has correct structure." << std::endl;
    }
    else if (STLCheck::isBinary_STL(mesh_file_path)) {
        std::cout << "The file is in binary STL format and has correct structure." << std::endl;
    }
    else {
        std::cout << "The file does not have a recognized STL format or has an incorrect structure." << std::endl;
    }
    NVO mesh;
    mesh.read_triangle_mesh(mesh_file_path);
    mesh.per_vertex_normals();
    mesh.compute_normal_distribution_on_sphere(std::numeric_limits<int>::max());
    TextureDrawer drawer;
    drawer.drawNormalsAndSaveDrawing("spherical_normals.txt", "texture_normals.png");
    

    return 0;
}
