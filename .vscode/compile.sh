#!/bin/bash

# Correctly getting the current working directory of the script.
workspacefolder=$(dirname "$(pwd)")

# Extract the name of the current directory.
name=$(basename "$workspacefolder")

echo "Please enter the directory name:"
read dir

# file name
file_name="$(dir)"

# Initialize a variable to hold all .cpp file names.
cpp_files=""

# Loop through all .cpp files in the source directory and add them to the list.
for file in "${workspacefolder}/source/${dir}/"*.cpp; do
    cpp_files="$cpp_files $file"
done

# Compile the source files using the list of .cpp files.
g++ $cpp_files -o "${workspacefolder}/tmp/bin/${dir}"

# Check if compilation was successful.
if [ $? -eq 0 ]; then
    echo "Compilation successful" >> "${workspacefolder}/tmp/log/compilation.log"
    # Execute the compiled program if needed
    "${workspacefolder}/tmp/bin/${dir}"
else
    echo "Compilation failed" >> "${workspacefolder}/tmp/log/compilation.log"
fi