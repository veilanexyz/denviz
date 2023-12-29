#include<texturen/texturen.hpp>
#include <iostream>

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " path to stl file" << std::endl;
        return 1;
    }

    std::string file = argv[1];
    Texture drawer;
    drawer.Heatmap(file);
}
