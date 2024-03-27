#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

directory="$1"

if [ ! -d "$directory" ]; then
    echo "The specified directory does not exist."
    exit 1
fi

report_file="insecurefile.txt"

echo "Checking permissions in '$directory' and its subdirectories:"
echo "---------------------------------------"


find "$directory" -type f | while read -r file; do
    permissions=$(stat -c "%a" "$file")

  
    if [ "$permissions" != "644" ]; then
        filename=$(basename "$file")  # Get only the filename without path
        echo "Insecure permissions found for file: $filename (Permissions: $permissions)"
        echo "$filename (Permissions: $permissions)" >> "$report_file"
    fi
done

echo "---------------------------------------"
echo "Permission check complete. Insecure files listed in '$report_file'."

