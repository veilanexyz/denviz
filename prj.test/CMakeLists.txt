add_executable(test test.cpp)

target_link_libraries(test PRIVATE data)
target_include_directories(test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../data/include
)