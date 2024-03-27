#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <directory> <extensions_file>"
    exit 1
fi

directory="$1"
extensions_file="$2"

if [ ! -d "$directory" ]; then
    echo "The specified directory does not exist."
    exit 1
fi

if [ ! -f "$extensions_file" ]; then
    echo "Extensions file '$extensions_file' does not exist."
    exit 1
fi

echo "Searching for files with specified extensions in '$directory'..."
echo "--------------------------------------------------------------"


extensions=($(cat "$extensions_file"))


for ext in "${extensions[@]}"; do
   
    subdirectory="$directory/$ext"
    mkdir -p "$subdirectory"

    
    find "$directory" -type f -iname "*.$ext" -exec mv {} "$subdirectory" \;
done

echo "--------------------------------------------------------------"
echo "File organization complete."

