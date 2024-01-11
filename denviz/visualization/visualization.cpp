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
#include "../data/include/data/data.hpp"

vtkSmartPointer<vtkActor> Visualization::generateSphereWithPoints(const std::vector<Point>& points, double opacity, double color[3], double radius ) const {
    // Create sphere
    vtkSmartPointer<vtkActor> sphereActor = createSphere(radius, color);
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
        double phi = point.phi;
        double theta = point.theta;
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

vtkSmartPointer<vtkActor> Visualization::createRealSphere(double radius, double color[3], double opacity) const {
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
    actor->GetProperty()->SetOpacity(opacity);

    // Геометрические данные
    sphereSource->Update();
    vtkPoints* points = sphereSource->GetOutput()->GetPoints();
    vtkSmartPointer<vtkFloatArray> textureCoordinates = vtkSmartPointer<vtkFloatArray>::New();
    textureCoordinates->SetNumberOfComponents(2);

    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
        double coord[3];
        points->GetPoint(i, coord);
        double phi = atan2(coord[1], coord[0]);
        double theta = acos(coord[2] / sphereSource->GetRadius());

        double s = static_cast<double>(phi + vtkMath::Pi()) / (2.0 * vtkMath::Pi());
        double t = static_cast<double>(theta) / vtkMath::Pi();

        textureCoordinates->InsertNextTuple2(s, t);
    }

    sphereSource->GetOutput()->GetPointData()->SetTCoords(textureCoordinates);

    return actor;
}

vtkSmartPointer<vtkActor> Visualization::Mapping(const std::string& imagePath, double radius, const double color[3], double opacity) const {
    // Создаем сферу
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(100);
    sphereSource->SetPhiResolution(100);
    sphereSource->SetRadius(radius);

    // Создаем маппер
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    // Создаем актер
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // Геометрические данные
    sphereSource->Update();
    vtkPoints* points = sphereSource->GetOutput()->GetPoints();
    vtkSmartPointer<vtkFloatArray> textureCoordinates = vtkSmartPointer<vtkFloatArray>::New();
    textureCoordinates->SetNumberOfComponents(2);

    for (vtkIdType i = 0; i < points->GetNumberOfPoints(); ++i) {
        double coord[3];
        points->GetPoint(i, coord);
        double phi = atan2(coord[1], coord[0]);
        double theta = acos(coord[2] / sphereSource->GetRadius());

        double s = static_cast<double>(phi + vtkMath::Pi()) / (2.0 * vtkMath::Pi());
        double t = static_cast<double>(theta) / vtkMath::Pi();

        textureCoordinates->InsertNextTuple2(s, t);
    }

    sphereSource->GetOutput()->GetPointData()->SetTCoords(textureCoordinates);

    // Создаем текстурный объект и читаем изображение в формате PNG
    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
    vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(imagePath.c_str());  // Указываем путь к файлу PNG
    texture->SetInputConnection(reader->GetOutputPort());

    // Устанавливаем цвет и прозрачность актеру
    actor->GetProperty()->SetColor(color[0], color[1], color[2]);
    actor->GetProperty()->SetOpacity(opacity);

    // Применяем текстуру к актеру
    actor->SetTexture(texture);

    return actor;
}
