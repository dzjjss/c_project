#!/bin/bash

# Get the current working directory of the script.
workspacefolder=$(pwd)

# The path to the source directory is now assumed to be directly under src.
src="${workspacefolder}/src"

# Create a timestamp for the log filename
timestamp=$(date +%y-%m-%d_%H:%M:%S)
log_file="${workspacefolder}/tmp/log/${timestamp}.build.log"

# Ensure the source directory exists
dir_check() {
    # Ensure the build directory and other necessary directories exist
    mkdir -p "${workspacefolder}/build"
    # Ensure the log directory exists, corrected to use workspace tmp directory
    mkdir -p "${workspacefolder}/tmp/log"
    # Ensure the bin directory exists
    mkdir -p "${workspacefolder}/bin"
    # ensure the lib directory exists
    mkdir -p "${workspacefolder}/build/lib"
    # ensure the arc directory exists
    mkdir -p "${workspacefolder}/build/arc"
}

build_picker() {
    # Ask the user which subdirectory of src to compile
    echo "Available subdirectories in src:"
    ls "${src}"

    while true; do
        echo "Please enter the name of the subdirectory you wish to compile:"
        read subdir

        # Check if the input is not empty and is a directory
        if [ -n "$subdir" ] && [ -d "${src}/${subdir}" ]; then
            break # exit the loop if input is valid
        else
            echo "Invalid input. Please enter a valid subdirectory name."
        fi
    done
}

cmake_file_generator() {
    # Start creating the CMakeLists.txt content in the root directory.
    cat <<EOF >${workspacefolder}/CMakeLists.txt
cmake_minimum_required(VERSION 3.0.0)
project(${subdir})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files from the specified subdirectory
file(GLOB SOURCES "\${PROJECT_SOURCE_DIR}/src/${subdir}/*.cpp")

# Add include directories
include_directories("\${PROJECT_SOURCE_DIR}/include")

# Add library directories
link_directories("\${PROJECT_SOURCE_DIR}/lib")

# 设置二进制文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/bin)

# 设置库文件的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/lib)

# 设置其他文件的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/arc)

# output compile_commands.json to the root directory for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add executable based on source files
add_executable(\${PROJECT_NAME} \${SOURCES})
EOF

    echo "CMakeLists.txt has been generated in the root directory for subdirectory ${subdir}."
}

clean_process() {
    rm ${workspacefolder}/compile_commands.json
    mv ${workspacefolder}/build/compile_commands.json ${workspacefolder}
    echo "Do you want to clean the build files? ([Y]/n):"
    read clean
    if [ "$clean" != "n" ]; then
        rm -rf "${workspacefolder}/build"
    fi
    echo "Do you want to clean the log files? ([Y]/n):"
    read clean
    if [ "$clean" != "n" ]; then
        rm "${workspacefolder}/tmp/log/${timestamp}.build.log"
    fi
}
build_process() {
    # Run CMake to configure the project and make to build it,
    # redirecting build logs to the same log file.
    cmake .. >"$log_file" 2>&1
    if make >>"$log_file" 2>&1; then
        echo "Build successful. Executable can be found in ${workspacefolder}/build/bin \n"

        # Execute the compiled program if needed
        echo "Do you want to run the compiled program? ([Y]/n):"
        read run
        if [ "$run" != "n" ]; then
            "${workspacefolder}/bin/${subdir}"
        fi
        clean_process
    else
        echo "Build failed. Check $log_file for errors."
    fi
}

main() {
    dir_check
    build_picker
    # Remove any existing CMakeLists.txt file in the root directory
    rm -f "${workspacefolder}/CMakeLists.txt"
    cmake_file_generator
    # Navigate to the build directory to configure CMake from there.
    cd "${workspacefolder}/build"
    build_process
    # Navigate back to the original directory
    cd "$workspacefolder"
}

main
