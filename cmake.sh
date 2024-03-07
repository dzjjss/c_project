#!/bin/bash

# Initialization function: Define basic variables and create necessary directories
initialize() {
    clear # Clear the screen
    # Get the current working directory of the script
    workspacefolder="$(pwd)"
    src="${workspacefolder}/src"
    timestamp=$(date +%y-%m-%d_%H:%M:%S)
    log_file="${workspacefolder}/tmp/log/${timestamp}.build.log"

    echo "Initializing directories..."
    mkdir -p "${workspacefolder}/build" "${workspacefolder}/tmp/log" \
        "${workspacefolder}/bin" "${workspacefolder}/build/lib" "${workspacefolder}/build/arc"
}

# Choose build directory
choose_build_directory() {
    clear # Clear the screen
    echo "Available subdirectories in src directory:"
    ls "${src}"

    while true; do
        echo "Please enter the name of the subdirectory you wish to compile:"
        read -r subdir
        if [ -n "$subdir" ] && [ -d "${src}/${subdir}" ]; then
            clear # Clear the screen after valid input
            break
        else
            clear # Clear the screen after invalid input
            echo "Invalid input. Please enter a valid subdirectory name."
            echo "Available subdirectories in src directory:"
            ls "${src}" # Display directory list again
        fi
    done
}

# Generate CMakeLists.txt file
generate_cmake_lists() {
    clear # Clear the screen
    cat <<EOF >"${workspacefolder}/CMakeLists.txt"
cmake_minimum_required(VERSION 3.0.0)
project(${subdir})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
file(GLOB SOURCES "\${PROJECT_SOURCE_DIR}/src/${subdir}/*.cpp")
include_directories("\${PROJECT_SOURCE_DIR}/include")
link_directories("\${PROJECT_SOURCE_DIR}/lib")
# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/arc)
# Generate compilation commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(\${PROJECT_NAME} \${SOURCES})
EOF

    echo "CMakeLists.txt generated for subdirectory ${subdir}."
}

# Build process
build_project() {
    clear # Clear the screen
    echo "Starting build process..."
    cd "${workspacefolder}/build" || exit
    if cmake .. >"$log_file" 2>&1 && make >>"$log_file" 2>&1; then
        clear # Clear the screen after successful build
        if [ -f "compile_commands.json" ]; then
            mv compile_commands.json "${workspacefolder}/"
        fi
        echo "Build successful. Executable files are located in ${workspacefolder}/bin"
    else
        clear # Clear the screen after build failure
        echo "Build failed. Please check $log_file for errors."
    fi
}

# Cleanup process
clean_up() {
    clear # Clear the screen
    echo "Do you want to clean build files? ([Y]/n):"
    read -r clean_build
    [ "${clean_build:-Y}" != "n" ] && rm -rf "${workspacefolder}/build"

    echo "Do you want to clean log files? ([Y]/n):"
    read -r clean_log
    [ "${clean_log:-Y}" != "n" ] && rm -f "${log_file}"
}

# Execute output files
execute_output() {
    clear # Clear the screen
    echo "Do you want to execute output files? ([Y]/n):"
    read -r execute
    if [ "${execute:-Y}" != "n" ]; then
        echo "Executing output files..."
        "${workspacefolder}/bin/${subdir}"
    fi
}

# Main function
main() {
    initialize
    choose_build_directory
    generate_cmake_lists
    build_project
    clean_up
    execute_output
    echo -e "\nScript execution completed."
}
main
