#!/bin/bash


if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi
target_directory="$1"

if [ ! -d "$target_directory" ]; then
    echo "The specified directory does not exist."
    exit 1
fi

find "$target_directory" -type f  |
while read -r text_file; do
  echo "Checking and cleaning $text_file..."
  
  sed -i '/^$/d' "$text_file"
  
  echo "Empty lines removed from $text_file"
done

echo "Empty line removal completed."
