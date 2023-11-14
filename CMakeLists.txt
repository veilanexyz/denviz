cmake_minimum_required(VERSION 3.10)

project(data)

set(VCPKG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}C:\vcpkg")

set(SFML_DIR "${VCPKG_ROOT}/installed/x64-windows/share/SFML")

find_package(SFML COMPONENTS graphics REQUIRED)

add_executable(data data.cpp)

target_include_directories(grafics PRIVATE "${VCPKG_ROOT}/installed/x64-windows/include")

target_link_libraries(grafics PRIVATE sfml-graphics)


