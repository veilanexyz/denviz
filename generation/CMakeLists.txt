cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(generation)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")
set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file" -G Ninja)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

# Set the vcpkg triplet
set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")

#set(VTK_DIR "${VCPKG_ROOT}/installed/x64-windows/share/vtk")
#find_package(VTK COMPONENTS core highgui imgcodecs imgproc videoio  REQUIRED )
#include_directories(${VTK_INCLUDE_DIRS})
SET(VTK_DIR "C:/dev/vcpkg/vcpkg/installed/x64-windows/include/vtk-9.2" CACHE PATH "VTK directory override" FORCE)
find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersSources
  IOGeometry
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
)

find_package(Threads)
 
if (NOT VTK_FOUND)

  message(FATAL_ERROR " spherebyvtk: Unable to find the VTK build folder.")
endif()


add_subdirectory(visualization)
add_subdirectory(prj.test)
add_subdirectory(data)
  
if(WIN32)
    set(VTK_RUNTIME_PATH "${VTK_DIR}/../../bin")
else()
    set(VTK_RUNTIME_PATH "${VTK_DIR}/../../lib")
endif()
install(TARGETS data DESTINATION bin)
install(DIRECTORY data/include/ DESTINATION include/data)
install(FILES data/data.cpp DESTINATION include/data)

install(DIRECTORY prj.test/ DESTINATION bin/prj.test)
install(FILES prj.test/test.cpp DESTINATION bin/prj.test)
install(FILES prj.test/CMakeLists.txt DESTINATION bin/prj.test)

install(TARGETS visualization DESTINATION bin)
install(DIRECTORY visualization/include/ DESTINATION include/visualization)
install(FILES visualization/visualization.cpp visualization/include/visualization/visualization.hpp DESTINATION include/visualization)

# Install OpenCV runtime files
install(FILES
        "${VTK_RUNTIME_PATH}/double-conversion.dll"
        "${VTK_RUNTIME_PATH}/fmtd.dll"
        "${VTK_RUNTIME_PATH}/jpeg62.dll"
        "${VTK_RUNTIME_PATH}/liblzma.dll"
        "${VTK_RUNTIME_PATH}/libpng16d.dll"
        "${VTK_RUNTIME_PATH}/lz4d.dll"
        "${VTK_RUNTIME_PATH}/pugixml.dll"
        "${VTK_RUNTIME_PATH}/tiffd.dll"
        "${VTK_RUNTIME_PATH}/vtkCommonColor-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkCommonComputationalGeometry-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkCommonCore-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkCommonDataModel-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkCommonExecutionModel-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkCommonMisc-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkCommonSystem-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkCommonTransforms-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkDICOMParser-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkFiltersCore-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkFiltersGeneral-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkFiltersGeometry-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkFiltersHybrid-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkFiltersSources-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkImagingCore-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkImagingSources-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkIOCore-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkIOGeometry-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkIOImage-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkkissfft-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkloguru-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkmetaio-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtkRenderingCore-9.2d.dll"
        "${VTK_RUNTIME_PATH}/vtksys-9.2d.dll"
        "${VTK_RUNTIME_PATH}/zlibd1.dll"
        DESTINATION bin)

# Install CMakeLists.txt files
install(FILES CMakeLists.txt DESTINATION .)
install(FILES data/CMakeLists.txt DESTINATION data)
install(FILES prj.test/CMakeLists.txt DESTINATION prj.test)
install(FILES visualization/CMakeLists.txt DESTINATION visualization)
