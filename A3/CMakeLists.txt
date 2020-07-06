cmake_minimum_required(VERSION 2.8)
project(ece650-a3)
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/run)

add_executable(ece650-a2 ece650-a2.cpp )
add_executable(ece650-a3 ece650-a3.cpp )
add_executable(rgen rgen.cpp )

install(PROGRAMS ece650-a1.py DESTINATION bin)
install(TARGETS  ece650-a2 ece650-a3 rgen RUNTIME DESTINATION bin)

set(LIBSRC graph.cpp graph.h)
add_library(graph ${LIBSRC})
target_link_libraries(ece650-a2 graph)
set_target_properties(ece650-a2 PROPERTIES COMPILE_FLAGS "-DUSE_GRAPH")

