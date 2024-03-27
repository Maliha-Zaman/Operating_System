#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <directory1> <directory2>"
    exit 1
fi

dir1="$1"
dir2="$2"

if [ ! -d "$dir1" ] || [ ! -d "$dir2" ]; then
    echo "Both arguments must be valid directories."
    exit 1
fi
diff -qr "dir1" "dir2"

