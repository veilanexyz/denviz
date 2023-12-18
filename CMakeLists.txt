add_subdirectory(data)
add_subdirectory(prj.test)


find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc)
    add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif(DOXYGEN_FOUND)

add_custom_target(build_all
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
        DEPENDS data prj.test
        COMMENT "Building all targets..."
)

if(NIBLACK_GENERATE_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(NIBLACK_DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(NIBLACK_DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)
        configure_file(${NIBLACK_DOXYGEN_IN} ${NIBLACK_DOXYGEN_OUT})
        add_custom_target(niblack_docs_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${NIBLACK_DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
        install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
                DESTINATION ./)
    else()
        message(STATUS "Couldn't find Doxygen")
    endif()
endif()
install(DIRECTORY prj.test/ DESTINATION bin/prj.test)
install(FILES prj.test/test.cpp DESTINATION bin/prj.test)
install(FILES prj.test/CMakeLists.txt DESTINATION bin/prj.test)

install(TARGETS data DESTINATION bin)
install(DIRECTORY data/include/ DESTINATION include/data)
install(FILES data/data.cpp data/include/data/data.hpp DESTINATION include/data)


# Install CMakeLists.txt files
install(FILES CMakeLists.txt DESTINATION .)
install(FILES data/CMakeLists.txt DESTINATION data)
