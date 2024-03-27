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

days_ago=20

find "$target_directory" -type f -mtime -$days_ago -exec ls -l {} \;
