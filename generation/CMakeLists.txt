cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

#option(BUILD_DOC "Build documentation" ON)

#find_package(Doxygen)

#if (DOXYGEN_FOUND)
  #  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${DOXYGEN_OUT} @ONLY)
    
  #message("Doxygen build started")

    #add_custom_target(doc_doxygen ALL
      #  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      #  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      #  COMMENT "Generating API documentation with Doxygen"
     #   VERBATIM
    #)
#else (DOXYGEN_FOUND)
  #  message("Doxygen need to be installed to generate the doxygen documentation")
#endif (DOXYGEN_FOUND)

#set_target_properties(generation PROPERTIES
#                      CONFIGURATIONS Release
#                      )

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

set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")

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
  message(FATAL_ERROR " generation: Unable to find the VTK build folder.")
endif()

set(SOURCES
    data/data.cpp
    prj.test/test.cpp
    visualization/visualization.cpp
)

add_executable(generation ${SOURCES})
target_link_libraries(generation PRIVATE data visualization)
target_link_libraries(generation PRIVATE ${VTK_LIBRARIES})

source_group("data" FILES data/data.cpp)
source_group("prj.test" FILES prj.test/test.cpp)
source_group("visualization" FILES visualization/visualization.cpp visualization/include/visualization/visualization.hpp)

add_subdirectory(visualization)
add_subdirectory(prj.test)
add_subdirectory(data)

set_target_properties(generation PROPERTIES
                      CONFIGURATIONS Release
                      )

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

if(VISUALIZATION_INSTALL_TARGET)
    install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*double-conversion.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*fmtd.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*jpeg62.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*liblzma.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*libpng16d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*lz4d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*pugixml.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*tiffd.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkCommonColor-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkCommonComputationalGeometry-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkCommonCore-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkCommonDataModel-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkCommonExecutionModel-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkCommonMisc-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkCommonSystem-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkCommonTransforms-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkDICOMParser-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkFiltersCore-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkFiltersGeneral-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkFiltersGeometry-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkFiltersHybrid-9.2d.dll*"
    )
        install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkFiltersSources-9.2d.dll*"
    )
            install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkImagingCore-9.2d.dll*"
    )
            install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkImagingSources-9.2d.dll*"
    )
            install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkIOCore-9.2d.dll*"
    )
            install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkkissfft-9.2d.dll*"
    )
            install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkloguru-9.2d.dll*"
    )
            install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkmetaio-9.2d.dll*"
    )
            install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtkRenderingCore-9.2d.dll*"
    )
                install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*vtksys-9.2d.dll*"
    )
                install(DIRECTORY "${VTK_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*zlibd1.dll*"
    )
endif()

# Install CMakeLists.txt files
install(FILES CMakeLists.txt DESTINATION .)
install(FILES data/CMakeLists.txt DESTINATION data)
install(FILES prj.test/CMakeLists.txt DESTINATION prj.test)
install(FILES visualization/CMakeLists.txt DESTINATION visualization)

vtk_module_autoinit(
  TARGETS  visualization
  MODULES ${VTK_LIBRARIES}
)

#set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
#set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#add_custom_target(
  #  documentation
  #  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
  #  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  #  COMMENT "Generating API documentation with Doxygen"
  #  VERBATIM
#)

#add_dependencies(visualization documentation)

