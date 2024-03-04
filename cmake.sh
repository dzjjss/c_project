#!/bin/bash


# Get the current working directory of the script.
workspacefolder=$(pwd)

# The path to the source directory is now assumed to be directly under src.
src="${workspacefolder}/src"

# Ensure the build directory and other necessary directories exist
mkdir -p "${workspacefolder}/build"
mkdir -p "${workspacefolder}/build/bin"  # Make sure the bin directory exists
mkdir -p "${workspacefolder}/tmp/log"  # Ensure the log directory exists, corrected to use workspace tmp directory

# Ask the user which subdirectory of src to compile
echo "Available subdirectories in src:"
ls "${src}"
echo "Please enter the name of the subdirectory you wish to compile:"
read subdir

# Validate that the user input corresponds to an existing directory
if [ ! -d "${src}/${subdir}" ]; then
    echo "The specified directory does not exist."
    exit 1
fi

# Remove any existing CMakeLists.txt file in the root directory
rm -f "${workspacefolder}/CMakeLists.txt"

# Create a timestamp for the log filename
timestamp=$(date +%Y-%m-%d_%H:%M:%S)
log_file="${workspacefolder}/tmp/log/${timestamp}.build.log"

# Start creating the CMakeLists.txt content in the root directory.
cat <<EOF > ${workspacefolder}/CMakeLists.txt
cmake_minimum_required(VERSION 3.0.0)
project(${subdir})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output directory for executables
set(EXECUTABLE_OUTPUT_PATH \${PROJECT_BINARY_DIR}/bin)

# Add source files from the specified subdirectory
file(GLOB SOURCES "\${PROJECT_SOURCE_DIR}/src/${subdir}/*.cpp")

# Add include directories
include_directories("\${PROJECT_SOURCE_DIR}/include")

# Add executable based on source files
add_executable(\${PROJECT_NAME} \${SOURCES})
EOF

echo "CMakeLists.txt has been generated in the root directory for subdirectory ${subdir}."

# Navigate to the build directory to configure CMake from there.
cd "${workspacefolder}/build"

# Run CMake to configure the project and make to build it,
# redirecting build logs to the same log file.
cmake .. > "$log_file" 2>&1
if make >> "$log_file" 2>&1; then
    echo "Build successful. Executable can be found in ${workspacefolder}/build/bin \n"
    # Execute the compiled program if needed
    echo "Do you want to run the compiled program? (y/n):"
    read run
    echo "\n"
    if [ "$run" = "y" ]; then
        "${workspacefolder}/build/bin/${subdir}"
    fi
else
    echo "Build failed. Check $log_file for errors."
fi

# Navigate back to the original directory
cd "$workspacefolder"
