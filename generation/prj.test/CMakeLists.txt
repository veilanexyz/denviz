add_executable(datatest  datatest.cpp)

target_link_libraries(datatest PRIVATE data)
target_link_libraries(datatest PRIVATE visualization)
target_include_directories(datatest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../data/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../visualization/include
        "${VTK_DIR}/../../include/vtk-9.2"
)
