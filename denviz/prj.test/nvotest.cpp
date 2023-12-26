#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkPNGWriter.h>
#include <vtkTexture.h>
#include <vtkPNGReader.h>
#include <vtkInteractorStyleTrackballCamera.h>  
#include <visualization/visualization.hpp>
#include <iostream>
#include <string>
#include <nvolib/nvolib.hpp>

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0] << " red green blue opacity radius" << std::endl;
        return 1;
    }

    double color[3];
    for (int i = 0; i < 3; ++i) {
        color[i] = std::stod(argv[i + 1]);
    }

    double opacity = std::stod(argv[4]);
    double radius = std::stod(argv[5]);
    Visualization visualization;

    // Создаем сферу
    vtkSmartPointer<vtkActor> sphereActor = visualization.createRealSphere(radius, color, opacity);

    // Сохраняем в STL
    vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
    stlWriter->SetFileName("sphere.stl");
    stlWriter->SetInputData(sphereActor->GetMapper()->GetInput());
    stlWriter->Write();

    // Проверяем, является ли STL файл бинарным
    STLCheck stlCheck;
    std::string stlFilename = "sphere.stl";
    if (stlCheck.isBinary_STL(stlFilename)) {
        std::cout << "The STL file is binary." << std::endl;
    }
    else {
        std::cout << "The STL file is ASCII." << std::endl;
    }

    // Вычисляем нормали и сохраняем их в файл
    NVO nvoSphere;
    nvoSphere.read_triangle_mesh("sphere.stl");
    nvoSphere.per_vertex_normals();
    nvoSphere.compute_normal_distribution_on_sphere(100);

    // Создаем текстуру на основе файла с нормалями и сохраняем ее
    TextureDrawer textureDrawer;
    textureDrawer.drawNormalsAndSaveDrawing("spherical_normals.txt", "output_texture.png");

    // Визуализируем сферу с текстурой
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkActor> texturedSphereActor = visualization.Mapping("output_texture.png", radius, color, opacity);
    renderer->AddActor(texturedSphereActor);

    // Создаем окно для визуализации
    vtkSmartPointer<vtkRenderWindow> render_window = vtkSmartPointer<vtkRenderWindow>::New();
    render_window->SetWindowName("Rendered Sphere");
    render_window->SetSize(800, 800);
    render_window->AddRenderer(renderer);

    // Добавляем интерактор и стиль взаимодействия
    vtkSmartPointer<vtkRenderWindowInteractor> render_window_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    render_window_interactor->SetInteractorStyle(style);
    render_window_interactor->SetRenderWindow(render_window);

    // Сохраняем изображения в формате PNG
    int outputCounter = 0;

    for (int i = 0; i < 6; ++i) {
        // Настраиваем камеру внутри цикла
        vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
        camera->SetPosition(0, 0, 5);
        camera->SetFocalPoint(0, 0, 0);

        camera->Azimuth(30 * i);
        camera->Elevation(10 * i);

        // Устанавливаем камеру для рендерера
        renderer->SetActiveCamera(camera);

        render_window->Render();

        // Сохраняем отрендеренное изображение с текстурированной сферой
        vtkSmartPointer<vtkWindowToImageFilter> render_window_to_image_filter = vtkSmartPointer<vtkWindowToImageFilter>::New();
        render_window_to_image_filter->SetInput(render_window);
        render_window_to_image_filter->Update();

        vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
        writer->SetFileName(("output_nvo" + std::to_string(outputCounter++) + ".png").c_str());
        writer->SetInputConnection(render_window_to_image_filter->GetOutputPort());
        writer->Write();
    }

    // Запускаем интерактор
    render_window_interactor->Start();

    return 0;
}

