add_library(visualization visualization.cpp include/visualization/visualization.hpp)
set_property(TARGET visualization PROPERTY CXX_STANDARD 20)
target_include_directories(visualization PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${VTK_INCLUDE_DIRS}
)
include_directories("${VCPKG_ROOT}/installed/x64-windows/include")
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
target_link_libraries(visualization PRIVATE ${VTK_LIBRARIES})
set_target_properties(visualization PROPERTIES OUTPUT_NAME "visualization")
install(TARGETS visualization)

vtk_module_autoinit(
  TARGETS  visualization
  MODULES ${VTK_LIBRARIES}
)
