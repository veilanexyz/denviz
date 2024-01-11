add_library(data data.cpp include/data/data.hpp)
set_property(TARGET data PROPERTY CXX_STANDARD 20)
target_include_directories(data PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS data)