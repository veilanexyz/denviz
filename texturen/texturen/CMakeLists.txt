add_library(texturen texturen.cpp include/texturen/texturen.hpp)
set_property(TARGET texturen PROPERTY CXX_STANDARD 20)

target_include_directories(texturen PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
include_directories( "${VCPKG_ROOT}/installed/x64-windows/include")

find_package(SFML COMPONENTS system window graphics REQUIRED)
target_link_libraries(texturen sfml-graphics)