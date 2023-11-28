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
