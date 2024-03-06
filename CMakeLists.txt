cmake_minimum_required(VERSION 3.0.0)
project(L4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files from the specified subdirectory
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/L4/*.cpp")

# Add include directories
include_directories("${PROJECT_SOURCE_DIR}/include")

# Add library directories
link_directories("${PROJECT_SOURCE_DIR}/lib")

# 设置二进制文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)

# 设置库文件的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 设置其他文件的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/arc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add executable based on source files
add_executable(${PROJECT_NAME} ${SOURCES})
