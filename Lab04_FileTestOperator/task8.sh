#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <directory> <size_in_bytes> <large_files_dir>"
    exit 1
fi

directory="$1"
size_in_bytes="$2"
large_files_dir="large_files"

if [ ! -d "$directory" ]; then
    echo "The specified directory does not exist."
    exit 1
fi

if [ ! -d "$large_files_dir" ]; then
    echo "Creating the 'large_files' directory..."
    mkdir -p "$large_files_dir"
fi

echo "Searching for files larger than $size_in_bytes bytes in '$directory'..."
echo "--------------------------------------------------------------"

find "$directory" -type f -size +"$size_in_bytes"c -exec mv -t "$large_files_dir" {} +

echo "--------------------------------------------------------------"
echo "File search complete."


