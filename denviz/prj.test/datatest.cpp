#include <data/data.hpp>
#include <visualization/visualization.hpp>
#include <iostream>
#include <string>
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
#include <vtkRendererCollection.h>

int main(int argc, char* argv[]) {
    if (argc < 8) {
        std::cerr << "Usage: " << argv[0] << " <type> <numPoints> <blurCoefficient> <phi_1> <theta_1> <phi_2> <theta_2> [phi_3 theta_3 phi_4 theta_4]" << std::endl;
        return 1;
    }

    std::string type = argv[1];
    int numPoints = std::stoi(argv[2]);
    double blurCoefficient = std::stod(argv[3]);
    double phi_1 = std::stod(argv[4]);
    double theta_1 = std::stod(argv[5]);
    double phi_2 = std::stod(argv[6]);
    double theta_2 = std::stod(argv[7]);

    std::string filename;
    std::string filename1;

    SphericalCoordinatesGenerator generator;
    Visualization visualization;

    if (type == "one_arc") {
        filename = "one_noisy_arc_coordinates.txt";
        std::vector<Point> points = generator.generatePointsOnArc(numPoints, phi_1, theta_1, phi_2, theta_2);
        std::vector<Point> noisyPoints = generator.addCoordinateNoiseOnSphere(points, blurCoefficient);
        generator.writePointsToFile(filename, noisyPoints);
    }
    else if (type == "from_point") {
        if (argc < 11) {
            std::cerr << "Usage for type from_point: " << argv[0] << " <type> <numPoints> <blurCoefficient> <phi_1> <theta_1> <phi_2> <theta_2> <phi_3> <theta_3> numArcs" << std::endl;
            return 1;
        }
        filename = "noisy_arcs_from_point.txt";
        double phi_3 = std::stod(argv[8]);
        double theta_3 = std::stod(argv[9]);
        double numArcs = std::stod(argv[10]);
        std::vector<Point> points = generator.generatePointsFromCenter(numArcs, numPoints, phi_1, theta_1, phi_2, theta_2, phi_3, theta_3);
        std::vector<Point> noisyPoints = generator.addCoordinateNoiseOnSphere(points, blurCoefficient);
        generator.writePointsToFile(filename, noisyPoints);
    }
    else if (type == "two_arcs") {
        if (argc < 12) {
            std::cerr << "Usage for type two_arcs: " << argv[0] << " <type> <numPoints> <blurCoefficient> <phi_1> <theta_1> <phi_2> <theta_2> <phi_3> <theta_3> <phi_4> <theta_4>" << std::endl;
            return 1;
        }
        filename = "first_noisy_arc_coordinates.txt";
        std::vector<Point> points1 = generator.generatePointsOnArc(numPoints, phi_1, theta_1, phi_2, theta_2);
        std::vector<Point> noisyPoints1 = generator.addCoordinateNoiseOnSphere(points1, blurCoefficient);
        generator.writePointsToFile(filename, noisyPoints1);

        filename1 = "second_noisy_arc_coordinates.txt";
        double phi_3 = std::stod(argv[8]);
        double theta_3 = std::stod(argv[9]);
        double phi_4 = std::stod(argv[10]);
        double theta_4 = std::stod(argv[11]);
        std::vector<Point> points2 = generator.generatePointsOnArc(numPoints, phi_3, theta_3, phi_4, theta_4);
        std::vector<Point> noisyPoints2 = generator.addCoordinateNoiseOnSphere(points2, blurCoefficient);
        generator.writePointsToFile(filename1, noisyPoints2);
    }
    else {
        std::cerr << "Invalid type. Supported types" << std::endl;
        return 1;
    }

    std::vector<Point> noisyPoints;
    if (filename1.empty()) {
        noisyPoints = generator.readPointsFromFile(filename);
    }
    else {
        // Concatenate points from two files for two_arcs case
        std::vector<Point> noisyPoints1 = generator.readPointsFromFile(filename);
        std::vector<Point> noisyPoints2 = generator.readPointsFromFile(filename1);
        noisyPoints.insert(noisyPoints.end(), noisyPoints1.begin(), noisyPoints1.end());
        noisyPoints.insert(noisyPoints.end(), noisyPoints2.begin(), noisyPoints2.end());
    }

    // Visualize the noisy points as spheres
    double opacity = 1.0;
    double color[3] = { 1.0, 0.0, 0.0 };
    double radius = 1.0;

    vtkSmartPointer<vtkActor> sphereActor = visualization.generateSphereWithPoints(noisyPoints, opacity, color, radius);

    // Create a renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.0, 0.0, 0.0); // Black background (White (1.0, 1.0, 1.0) )

    // Add the actor to the renderer
    renderer->AddActor(sphereActor);

    // Create a render window
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetWindowName("Noisy Spheres");
    renderWindow->SetSize(800, 800);

    // Set the renderer for the render window
    renderWindow->AddRenderer(renderer);

    // Create a render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);  // Set the render window for the interactor

    // Start the rendering loop
    renderWindow->Render();
    //renderWindowInteractor->Start();

    // Save images in PNG format
    int outputCounter = 0;

    for (int i = 0; i < 6; ++i) {
        // Configure the camera inside the loop
        vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
        camera->SetPosition(0, 0, 5);
        camera->SetFocalPoint(0, 0, 0);

        camera->Azimuth(30 * i);
        camera->Elevation(10 * i);

        // Set the camera for the renderer
        renderer->SetActiveCamera(camera);

        renderWindow->Render();

        vtkSmartPointer<vtkWindowToImageFilter> render_window_to_image_filter = vtkSmartPointer<vtkWindowToImageFilter>::New();
        render_window_to_image_filter->SetInput(renderWindow);
        render_window_to_image_filter->Update();

        vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
        writer->SetFileName(("output_data" + std::to_string(outputCounter++) + ".png").c_str());
        writer->SetInputConnection(render_window_to_image_filter->GetOutputPort());
        writer->Write();
    }

    renderWindowInteractor->Start();

    return 0;
}
