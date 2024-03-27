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

find "$target_directory" -type f | sed -n 's/.*\.\([^\.]*\)$/\1/p' | sort | uniq -c |
while read -r count extension; do
  echo "File type: .$extension - Count: $count"
done

