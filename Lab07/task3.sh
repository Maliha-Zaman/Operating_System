#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi
target_directory="$1"

if [ ! -d "$target_directory" ]; then
    echo "The specified directory does not exist."
    exit 1
fi


replace_text="$2"

find "$target_directory" -type f |
while read -r file; do
  echo "Replacing text in $file..."
  
  echo "$replace_text" > "$file"
  
  echo "Text replaced in $file"
done

echo "Text replacement completed."
