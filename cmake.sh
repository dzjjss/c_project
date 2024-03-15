#!/bin/bash

# Initialization function: Define basic variables and create necessary directories
initialize() {
    clear # Clear the screen
    # Get the current working directory of the script
    workspacefolder="$(pwd)"
    src="${workspacefolder}/src"
    cache_folder="${workspacefolder}/.cache"
    cache_file="${cache_folder}/last_subdir.cache"
    timestamp=$(date +%y-%m-%d_%H:%M:%S)
    log_file="${workspacefolder}/tmp/log/${timestamp}.build.log"

    echo "\033[36mInitializing directories...\033[0m"
    mkdir -p "${workspacefolder}/build" "${workspacefolder}/tmp/log" \
        "${workspacefolder}/bin" "${workspacefolder}/build/lib" "${workspacefolder}/build/arc" "${cache_folder}"
}

# Choose the build directory
choose_build_directory() {
    clear # Clear the screen
    echo "\033[34mAvailable subdirectories in src:\033[0m"
    ls "${src}"

    # Check if cache file exists and read the last choice
    last_subdir=""
    if [ -f "${cache_file}" ]; then
        last_subdir=$(cat "${cache_file}")
        echo "\033[33mLast chosen subdir was: \033[32m${last_subdir}\033[0m"
    fi

    while true; do
        echo "\033[33mPlease enter the name of the subdir you wish to compile[\033[32m${last_subdir}\033[33m]:\033[0m"
        read -r subdir
        if [ -z "$subdir" ] && [ -n "${last_subdir}" ]; then
            subdir=${last_subdir}
        fi
        if [ -n "$subdir" ] && [ -d "${src}/${subdir}" ]; then
            clear # Clear the screen after a valid input
            echo "\033[32mCurrent chosen subdir: ${subdir}\033[0m"
            break
        else
            clear # Clear the screen after an invalid input
            echo "\033[31mInvalid input. Please enter a valid subdir name.\033[0m"
            echo "\033[34mAvailable subdirectories in src:\033[0m"
            ls "${src}" # Show the directory list again
        fi
    done

    # Save current choice to cache file
    echo "${subdir}" >"${cache_file}"
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
# Set binary file output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/arc)
# Generate compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(\${PROJECT_NAME} \${SOURCES})
EOF

    echo "\033[32mGenerated CMakeLists.txt for subdir ${subdir}.\033[0m"
}

# Build process
build_project() {
    clear # Clear the screen
    echo "\033[36mStarting build process...\033[0m"
    cd "${workspacefolder}/build" || exit

    # Clear previous build executable file
    rm -f "${workspacefolder}/bin/${subdir}"

    if cmake .. >"$log_file" 2>&1 && make >>"$log_file" 2>&1; then
        # Check if binary file was successfully generated
        if [ -f "${workspacefolder}/bin/${subdir}" ]; then
            clear # Clear the screen after a successful build
            if [ -f "compile_commands.json" ]; then
                mv compile_commands.json "${workspacefolder}/"
            fi
            echo "\033[32mBuild succeeded. Executable located in ${workspacefolder}/bin.\033[0m"
            build_success=true # Set build success flag
        else
            clear # Clear the screen if binary file was not generated
            echo "\033[31mBuild failed, executable not found. Please check the log file $log_file for errors.\033[0m"
            build_success=false # Set build failure flag
        fi
    else
        clear # Clear the screen if cmake or make failed
        echo "\033[31mBuild failed. Please check the log file $log_file for errors.\033[0m"
        build_success=false # Set build failure flag
    fi
}

# Clean up process
clean_up() {
    if [ "$build_success" = true ]; then
        echo "\033[36mClean-up options:\033[0m"
        echo "1. \033[33mClean both build and log files\033[0m"
        echo "2. \033[33mClean build files\033[0m"
        echo "3. \033[33mDo not clean\033[0m"
        echo "\033[36mPlease choose an option ([1]/2/3):\033[0m"
        read -r cleanup_option

        # Check for empty input, default option 1
        if [ -z "$cleanup_option" ]; then
            cleanup_option=1
        fi

        case $cleanup_option in
        1)
            echo "\033[32mCleaning both build and log files...\033[0m"
            rm -rf "${workspacefolder}/build"
            rm -f "${workspacefolder}/tmp/log/"*
            ;;
        2)
            echo "\033[32mCleaning build files...\033[0m"
            rm -rf "${workspacefolder}/build"
            ;;
        3)
            echo "\033[32mNo clean-up performed.\033[0m"
            ;;
        *)
            echo "\033[31mInvalid option. No clean-up performed.\033[0m"
            ;;
        esac
    else
        echo "\033[36mWould you like to clean build files? ([Y]/n):\033[0m"
        read -r clean_build
        if [ "${clean_build:-Y}" != "n" ]; then
            echo "\033[32mCleaning build files...\033[0m"
            rm -rf "${workspacefolder}/build"
        fi
        echo "\033[33mLog file kept for debugging: $log_file\033[0m"
    fi
}

# Execute output file
execute_output() {
    clear # Clear the screen
    echo "\033[36mExecute the output file? ([Y]/n):\033[0m"
    read -r execute
    if [ "${execute:-Y}" != "n" ]; then
        echo "\033[32mExecuting output file...\033[0m"
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
    echo "\033[32m\nScript completed.\033[0m"
}
main
