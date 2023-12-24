add_library(visualization visualization.cpp include/visualization/visualization.hpp)
set_property(TARGET visualization PROPERTY CXX_STANDARD 20)
target_include_directories(visualization PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
include_directories("${VCPKG_ROOT}/installed/x64-windows/include")
target_link_libraries(visualization PUBLIC ${VTK_LIBRARIES})
set_target_properties(visualization PROPERTIES OUTPUT_NAME "visualization")
install(TARGETS visualization)

export(TARGETS visualization FILE VisualizationTargets.cmake)

include("${VTK_USE_FILE}")

vtk_module_autoinit(
  TARGETS  visualization
  MODULES ${VTK_LIBRARIES}
)
