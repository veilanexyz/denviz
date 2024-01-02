#include <nvolib/nvolib.hpp>
#include <igl/read_triangle_mesh.h>
#include <igl/per_vertex_normals.h>
#include <fstream>
#include <stb_image_write.h>


bool NVO::read_triangle_mesh(const std::string& filename) {
    return igl::read_triangle_mesh(filename, V, F);
}

void NVO::per_vertex_normals() {
    igl::per_vertex_normals(V, F, N);
}

void NVO::compute_normal_distribution_on_sphere(int num_samples) {
    
    if (N.rows() == 0) {
        std::cerr << "Error: Per-vertex normals are not computed." << std::endl;
        return;
    }

    Eigen::MatrixXd spherical_normals(N.rows(), 2);
    for (int i = 0; i < N.rows(); ++i) {
        double theta = std::acos(N(i, 2));
        double phi = std::atan2(N(i, 1), N(i, 0));
        spherical_normals(i, 0) = theta;
        spherical_normals(i, 1) = phi;
    }
    std::ofstream out_file("spherical_normals.txt");
    if (out_file.is_open()) {
        out_file << spherical_normals;
        out_file.close();
        std::cout << "Spherical normals saved to spherical_normals.txt" << std::endl;
    }
    else {
        std::cerr << "Error saving spherical normals to file." << std::endl;
    }
}


void TextureDrawer::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    float x, y;
    while (file >> x >> y) {
        normals.emplace_back(x, y);
    }

    file.close();
}

void TextureDrawer::drawNormalsAndSaveDrawing(const std::string& txtFilename, const std::string& pngFilename) {
    loadFromFile(txtFilename);

    sf::RenderTexture renderTexture;
    renderTexture.create(95, 95);

    renderTexture.clear(sf::Color::Black);

    sf::VertexArray points(sf::Points);
    for (const auto& normal : normals) {
        points.append(sf::Vertex(normal, sf::Color::Red));
        float scale = 30.0f;
        points.append(sf::Vertex(normal + scale * normal, sf::Color::Red));
    }

    renderTexture.draw(points);
    renderTexture.display();

    sf::Sprite sprite(renderTexture.getTexture());
    window.clear();
    window.draw(sprite);
    window.display();

    sf::Texture texture = renderTexture.getTexture();
    sf::Image screenshot = texture.copyToImage();

    if (screenshot.saveToFile(pngFilename)) {
        std::cout << "Drawing saved to " << pngFilename << std::endl;
    }
    else {
        std::cerr << "Error: Unable to save drawing to " << pngFilename << std::endl;
    }
}
  
bool STLCheck::isASCII_STL(const std::string& filename) {
    std::ifstream stlFile(filename);
    if (!stlFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    bool hasFacetNormal = false;
    bool hasOuterLoop = false;
    bool hasVertex = false;

    while (std::getline(stlFile, line)) {
        if (line.find("facet normal") != std::string::npos) {
            hasFacetNormal = true;
        }
        else if (line.find("outer loop") != std::string::npos) {
            hasOuterLoop = true;
        }
        else if (line.find("vertex") != std::string::npos) {
            hasVertex = true;
        }
    }

    stlFile.close();

    return hasFacetNormal && hasOuterLoop && hasVertex;
}

bool STLCheck::isBinary_STL(const std::string& filename) {
    std::ifstream stlFile(filename, std::ios::binary);
    if (!stlFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

   
    stlFile.seekg(0, std::ios::end);
    size_t fileSize = stlFile.tellg();
    stlFile.seekg(0, std::ios::beg);

    
    if (fileSize < 84) {
        std::cerr << "Binary STL file size is too small." << std::endl;
        stlFile.close();
        return false;
    }
    std::vector<char> header(80);
    stlFile.read(header.data(), 80);

    
    int numFacets;
    stlFile.read(reinterpret_cast<char*>(&numFacets), sizeof(int));

    size_t expectedSize = 80 + 4 + 50 * static_cast<size_t>(numFacets);
    stlFile.close();

    return fileSize == expectedSize;
}

//void visualize_normals(const std::vector<std::vector<double>>& points, double opacity) {
//    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
//    vtkSmartPointer<vtkPoints> vtkPointsObj = vtkSmartPointer<vtkPoints>::New();
//
//    for (const auto& point : points) {
//        double theta = point[1];
//        double phi = point[2];
//        double radius = point[3];
//
//        double x = radius * sin(phi) * cos(theta);
//        double y = radius * sin(phi) * sin(theta);
//        double z = radius * cos(phi);
//
//        vtkPointsObj->InsertNextPoint(x, y, z);
//
//        // Добавляем сферу с текущим радиусом
//        sphereSource->SetCenter(x, y, z);
//        sphereSource->SetRadius(radius);
//        sphereSource->Update(); // Обновляем данные сферы
//
//        // Создаем mapper и actor для сферы
//        vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//        sphereMapper->SetInputData(sphereSource->GetOutput());
//
//        vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
//        sphereActor->SetMapper(sphereMapper);
//
//        // Устанавливаем прозрачность и добавляем в renderer
//        sphereActor->GetProperty()->SetOpacity(opacity);
//        renderer->AddActor(sphereActor);
//    }
//
//    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
//    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renderWindow->AddRenderer(renderer);
//
//    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    renderWindowInteractor->SetRenderWindow(renderWindow);
//
//    renderer->SetBackground(1, 1, 1);
//
//    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
//    colorTransferFunction->AddRGBPoint(0.0, 1.0, 0.0, 0.0);
//
//    // Устанавливаем параметры цветовой схемы для сфер
//    sphereActor->GetProperty()->SetColor(colorTransferFunction->GetColor(opacity));
//
//    renderWindow->Render();
//    renderWindowInteractor->Start();
//    std::cout << "Количество точек: " << points.size() << std::endl;
//}