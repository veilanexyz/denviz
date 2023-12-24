Cmake_minimum_required(VERSION 3.12)
project(nvolib)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file" -G Ninja)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")
#set(VCPKG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}C:\vcpkg")

#set(SFML_DIR "${VCPKG_ROOT}/installed/x64-windows/share/SFML")
set(libigl_DIR "${vcpkg_root}/installed/x86-windows/share/libigl")
set(libigl_DIR "${libigl_DIR}" CACHE PATH "Path to libiglConfig.cmake or libigl-config.cmake" FORCE)

set(SFML_DIR "${VCPKG_ROOT}/installed/x64-windows/share/SFML")
# Устанавливаем переменную для CMake
set(sfml_DIR "${sfml_DIR}" CACHE PATH "Path to SFMLConfig.cmake or SFML-config.cmake" FORCE)
#set(SFML_DIR "${VCPKG_ROOT}/installed/x64-windows/share/SFML")

find_package(libigl CONFIG REQUIRED)
find_package(SFML COMPONENTS graphics REQUIRED)

#find_package(Stb REQUIRED)
 
add_subdirectory(nvolib)
add_subdirectory (tester)

option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

if(WIN32)
    set(libigl_RUNTIME_PATH "${LIBIGL_INCLUDE_DIRS}/../../bin")
else()
    set(libigl_RUNTIME_PATH "${LIBIGL_INCLUDE_DIRS}/../../lib")
endif()
if(WIN32)
    set(sfml_RUNTIME_PATH "${SFML_INCLUDE_DIRS}/../../bin")
else()
    set(l_RUNTIME_PATH "${SFML_INCLUDE_DIRS}/../../lib")
endif()

if(INSTALL_TARGET)
    install(DIRECTORY "${LIBIGL_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*libpng16d.dll*"
    )
endif()
if(INSTALL_TARGET)
    install(DIRECTORY "${SFML_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*sfml-graphics-d-2.dll*"
    )
    install(DIRECTORY "${SFML_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*sfml-system-d-2.dll*"
    )
    install(DIRECTORY "${SFML_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*sfml-window-d-2.dll*"
    )
endif()
install(TARGETS nvolib DESTINATION bin)
               # RUNTIME DESTINATION bin
                #LIBRARY DESTINATION lib 
                #ARCHIVE DESTINATION static)
install(DIRECTORY nvolib/include/ DESTINATION include/nvolib)
install(FILES nvolib/nvolib.cpp DESTINATION nvolib)
install(TARGETS tester DESTINATION bin)
install(DIRECTORY tester/ DESTINATION bin/)
install(DIRECTORY cmake/ DESTINATION .)