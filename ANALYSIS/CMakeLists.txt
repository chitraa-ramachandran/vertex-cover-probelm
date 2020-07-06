cmake_minimum_required(VERSION 2.8)
project(a4-ece650)

if (EXISTS "${CMAKE_SOURCE_DIR}/minisat")
  add_subdirectory(minisat)
else()
  message (FATAL_ERROR "MiniSat not found. Use `git clone https://github.com/agurfinkel/minisat` to check it out.")
endif()


## ECE650 Specific configuration start here
## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/run)
# expose minisat header files
include_directories(${CMAKE_SOURCE_DIR}/minisat)
set(LIBSRC graph.cpp graph.h)
add_library(graph ${LIBSRC})

set(LIBSRCC avc1.cpp avc1.h)
add_library(avc1 ${LIBSRCC})

set(LIBSRCC avc2.cpp avc2.h)
add_library(avc2 ${LIBSRCC})

set(LIBSRCC minvc.cpp minvc.h)
add_library(minvc ${LIBSRCC})


#set(LIBSRCC runtime.cpp runtime.h)
#add_library(runtime ${LIBSRCC})

# create the main executable
## add additional .cpp files if needed
add_executable(ece650-prj ece650-prj.cpp)
#add_executable(driver driver.cpp)
#install(TARGETS ece650-prj  RUNTIME DESTINATION bin)
# link MiniSAT libraries
target_link_libraries(minvc minisat-lib-static)
target_link_libraries(ece650-prj minisat-lib-static)
target_link_libraries(ece650-prj graph)
target_link_libraries(ece650-prj avc1)
target_link_libraries(ece650-prj avc2)
target_link_libraries(ece650-prj minvc)
#target_link_libraries(ece650-prj runtime)
TARGET_LINK_LIBRARIES(ece650-prj pthread)
#install(TARGETS ece650-prj driver RUNTIME DESTINATION bin)

