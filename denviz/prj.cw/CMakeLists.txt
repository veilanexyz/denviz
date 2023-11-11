cmake_minimum_required(VERSION 3.23)
project(data LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

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

find_package(SFML REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

if(WIN32)
    set(SFML_RUNTIME_PATH "${SFML_DIR}/../../bin")
else()
    set(SFML_RUNTIME_PATH "${SFML_DIR}/../../lib")
endif()

add_subdirectory(data)
add_subdirectory(prj.test)

add_custom_target(build_all
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
        DEPENDS data prj.test
        COMMENT "Building all targets..."
)

install(DIRECTORY prj.test/ DESTINATION bin/prj.test)
install(FILES prj.test/test.cpp DESTINATION bin/prj.test)
install(FILES prj.test/CMakeLists.txt DESTINATION bin/prj.test)

install(TARGETS data DESTINATION bin)
install(DIRECTORY data/include/ DESTINATION include/data)
install(FILES data/data.cpp data/include/data/data.hpp DESTINATION include/data)


# Install CMakeLists.txt files
install(FILES CMakeLists.txt DESTINATION .)
install(FILES data/CMakeLists.txt DESTINATION data)
