 
add_executable(test test.cpp)

target_link_libraries(test PRIVATE data)
target_link_libraries(test PRIVATE visualization)
target_include_directories(test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../data/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../visualization/include
        "${VTK_DIR}/../../include/vtk-9.2"
)
