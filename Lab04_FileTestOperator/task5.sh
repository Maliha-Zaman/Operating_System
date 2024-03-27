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

total_size=$(du -ch "$directory" | grep "total$" | awk '{print $1}')

echo "Total size of files in '$directory' and its subdirectories:"
echo "$total_size"

