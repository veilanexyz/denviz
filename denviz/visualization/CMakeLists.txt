add_library(visualization visualization.cpp include/visualization/visualization.hpp)
set_property(TARGET visualization PROPERTY CXX_STANDARD 20)
target_include_directories(visualization PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

#add_library(data data.cpp include/data/data.hpp)   
#set_property(TARGET data PROPERTY CXX_STANDARD 20)
#target_include_directories(data PUBLIC
 # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/data>
 #  $<INSTALL_INTERFACE:include/data>
#)

include_directories("${VCPKG_ROOT}/installed/x64-windows/include")
target_link_libraries(visualization data ${VTK_LIBRARIES})
install(TARGETS visualization)
install(TARGETS data)

vtk_module_autoinit(
  TARGETS  visualization
  MODULES ${VTK_LIBRARIES}
)