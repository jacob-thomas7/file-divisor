# Version requirements
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

# Project information
project(FileDivisor VERSION 0.0.1 LANGUAGES CXX)
set(LIBRARY_TYPE SHARED) # Supports STATIC or SHARED

# Generate config file
configure_file(source/library/include/config.hpp.in ${CMAKE_BINARY_DIR}/generated/config.hpp)
include_directories(${CMAKE_BINARY_DIR}/generated/)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Library
add_library(${PROJECT_NAME} ${LIBRARY_TYPE}
    source/library/src/search.cpp
)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME file-divisor)
include_directories(${CMAKE_SOURCE_DIR}/source/library/include)

# CLI Executable
add_executable(${PROJECT_NAME}_CLI
    source/cli_executable/main.cpp
)
set_target_properties(${PROJECT_NAME}_CLI PROPERTIES OUTPUT_NAME divisor)
target_link_libraries(${PROJECT_NAME}_CLI PUBLIC ${PROJECT_NAME})

# GUI Executable
# add_executable(${PROJECT_NAME}_GUI WIN32
#    source/gui_executable/main.cpp
# )
# set_target_properties(${PROJECT_NAME}_GUI PROPERTIES OUTPUT_NAME divisor-gui)
# target_link_libraries(${PROJECT_NAME}_GUI PUBLIC ${PROJECT_NAME})

# Test Suite Executable
add_executable(${PROJECT_NAME}_TEST
    tests/main.cpp
)
set_target_properties(${PROJECT_NAME}_TEST PROPERTIES OUTPUT_NAME divisor-tests)
target_link_libraries(${PROJECT_NAME}_TEST PUBLIC ${PROJECT_NAME})