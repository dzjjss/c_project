cmake_minimum_required(VERSION 3.0.0)
project(L4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output directory for executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Add source files from the specified subdirectory
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/L4/*.cpp")

# Add include directories
include_directories("${PROJECT_SOURCE_DIR}/include")

# Add executable based on source files
add_executable(${PROJECT_NAME} ${SOURCES})
