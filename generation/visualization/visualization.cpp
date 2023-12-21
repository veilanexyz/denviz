#include <visualization/visualization.hpp>
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
#include <iostream>

vtkSmartPointer<vtkActor>   Visualization::generateSphereWithPoints(const std::vector<std::vector<double>>& points, double opacity, double color[3], double radius, double sphereColor[4]) const {
    // Create sphere
    vtkSmartPointer<vtkActor> sphereActor = createSphere(radius, sphereColor);
    // Get polydata from the sphere
    vtkSmartPointer<vtkPolyData> spherePolyData = vtkPolyData::SafeDownCast(sphereActor->GetMapper()->GetInput());
    if (!spherePolyData) {
        std::cerr << "Failed to obtain polydata from the sphere." << std::endl;
        return nullptr;
    }
    // Create vertices
    vtkSmartPointer<vtkPoints> pointsVTK = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");
    for (const auto& point : points) {
        double phi = point[0];
        double theta = point[1];
        // Convert spherical coordinates to Cartesian coordinates
        double x = sin(theta) * cos(phi);
        double y = sin(theta) * sin(phi);
        double z = cos(theta);

        pointsVTK->InsertNextPoint(x * radius, y * radius, z * radius);
        vertices->InsertNextCell(1);
        vertices->InsertCellPoint(pointsVTK->GetNumberOfPoints() - 1);

        unsigned char rgb[3];
        for (int i = 0; i < 3; ++i) {
            rgb[i] = static_cast<unsigned char>(255 * std::min(1.0, std::max(0.0, color[i])));
        }
        colors->InsertNextTypedTuple(rgb);
    }
    // Add points to polydata
    spherePolyData->SetPoints(pointsVTK);
    spherePolyData->SetVerts(vertices);
    spherePolyData->GetPointData()->SetScalars(colors);
    // Set actor properties
    vtkSmartPointer<vtkProperty> property = vtkSmartPointer<vtkProperty>::New();
    property->SetOpacity(opacity);
    sphereActor->SetProperty(property);
    // Set polydata as input for the mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(spherePolyData);
    // Set mapper for the actor
    sphereActor->SetMapper(mapper);

    return sphereActor;
}

vtkSmartPointer<vtkActor>  Visualization::createSphere(double radius, double color[3]) const {
    // Create a sphere source
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(100);
    sphereSource->SetPhiResolution(100);
    sphereSource->SetRadius(radius);
    // Create mapper
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    // Create actor
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(color);

    return actor;
}

void Mapping(const std::string& imagePath, const std::string& stlPath = "output.stl") {
    // Создаем сферу
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetThetaResolution(100);
    sphere->SetPhiResolution(50);

    // Создаем маппер
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphere->GetOutputPort());

    // Создаем актер
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Задаем текстурные координаты
    sphere->Update();
    vtkPoints* points = sphere->GetOutput()->GetPoints();
    vtkSmartPointer<vtkFloatArray> textureCoordinates = vtkSmartPointer<vtkFloatArray>::New();
    textureCoordinates->SetNumberOfComponents(2);

    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
        double coord[3];
        points->GetPoint(i, coord);
        double phi = atan2(coord[1], coord[0]);
        double theta = acos(coord[2] / sphere->GetRadius());

        double s = static_cast<double>(phi + vtkMath::Pi()) / (2.0 * vtkMath::Pi());
        double t = static_cast<double>(theta) / vtkMath::Pi();

        textureCoordinates->InsertNextTuple2(s, t);
    }

    sphere->GetOutput()->GetPointData()->SetTCoords(textureCoordinates);

    // Создаем текстурный объект и читаем изображение в формате PNG
    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
    vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(imagePath.c_str());  // Указываем путь к файлу PNG
    texture->SetInputConnection(reader->GetOutputPort());

    // Применяем текстуру к актеру
    actor->SetTexture(texture);

    // Создаем рендерер
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.0, 0.0, 0.0);  // белый фон

    // Добавляем актер в рендерер
    renderer->AddActor(actor);

    // Создаем окно для визуализации
    vtkSmartPointer<vtkRenderWindow> render_window = vtkSmartPointer<vtkRenderWindow>::New();
    render_window->SetWindowName("Texture Mapping");
    render_window->SetSize(1000, 1200);
    render_window->AddRenderer(renderer);

    // Создаем интерактор
    vtkSmartPointer<vtkRenderWindowInteractor> render_window_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    render_window_interactor->SetRenderWindow(render_window);

    for (int i = 0; i < 6; ++i) {
        // Создаем новую камеру
        vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
        camera->SetPosition(0, 0, 5);  // Перемещаем камеру по оси Z
        camera->SetFocalPoint(0, 0, 0);  // Устанавливаем фокус камеры

        // Устанавливаем углы азимута и углов места
        camera->Azimuth(20 * i);
        camera->Elevation(10 * i);

        // Устанавливаем камеру для рендеринга
        renderer->SetActiveCamera(camera);

        // Запускаем рендеринг
        render_window->Render();

        // Сохраняем результат в файл в формате PNG
        vtkSmartPointer<vtkWindowToImageFilter> render_window_to_image_filter = vtkSmartPointer<vtkWindowToImageFilter>::New();
        render_window_to_image_filter->SetInput(render_window);
        render_window_to_image_filter->Update();

        vtkSmartPointer<vtkPNGWriter> writer = vtkSmartPointer<vtkPNGWriter>::New();
        writer->SetFileName(("output_" + std::to_string(i) + ".png").c_str());
        writer->SetInputConnection(render_window_to_image_filter->GetOutputPort());
        writer->Write();


        // Сохраняем результат в файл в формате STL
        vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
        stlWriter->SetFileName(stlPath.c_str());
        stlWriter->SetInputConnection(sphere->GetOutputPort());
        stlWriter->Write();
    }
    // Запускаем интерактор
    render_window_interactor->Start();
}



