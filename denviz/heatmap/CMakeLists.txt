add_library(heatmap heatmap.cpp include/heatmap/heatmap.hpp)
set_property(TARGET heatmap PROPERTY CXX_STANDARD 20)

target_include_directories(heatmap PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
include_directories( "${VCPKG_ROOT}/installed/x64-windows/include")

find_package(SFML COMPONENTS system window graphics REQUIRED)
target_link_libraries(heatmap sfml-graphics)