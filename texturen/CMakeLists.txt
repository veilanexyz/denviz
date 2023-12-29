cmake_minimum_required(VERSION 3.0)

project(texturen)

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

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)


source_group("prj.test" FILES prj.test/test.cpp)
source_group("texturen" FILES texturen/texturen.cpp texturen/include/texturen/texturen.hpp)

add_subdirectory(texturen)
add_subdirectory(prj.test)

if(WIN32)
    set(VTK_RUNTIME_PATH "${VTK_DIR}/../../bin")
else()
    set(VTK_RUNTIME_PATH "${VTK_DIR}/../../lib")
endif()

install(DIRECTORY prj.test/ DESTINATION bin/prj.test)
install(FILES prj.test/datatest.cpp DESTINATION bin/prj.test)
install(FILES prj.test/CMakeLists.txt DESTINATION bin/prj.test)

install(TARGETS texturen DESTINATION bin)
install(DIRECTORY texturen/include/ DESTINATION include/texturen)
install(FILES texturen/texturen.cpp texturen/include/texturen/texturen.hpp DESTINATION include/texturen)

# Install CMakeLists.txt files
install(FILES CMakeLists.txt DESTINATION .)
install(FILES prj.test/CMakeLists.txt DESTINATION prj.test)
install(FILES texturen/CMakeLists.txt DESTINATION texturen)

