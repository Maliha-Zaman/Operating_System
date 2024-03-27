#!/bin/bash


timestamp=$(date +'%Y%m%d_%H%M%S')

read -p "Enter the directory path: " directory_path
read -p "Enter the file extension (e.g., txt, jpg): " extension


if [ ! -d "$directory_path" ]; then
    echo "Directory does not exist."
    exit 1
fi


for file in "$directory_path"/*."$extension"; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        new_filename="${timestamp}_${filename}"
        new_path="$directory_path/$new_filename"
        
        # Rename the file
        mv "$file" "$new_path"
        echo "Renamed $filename to $new_filename"
    fi
done

