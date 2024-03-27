#!/bin/bash

if [ $# -ne 1 ]; then
    echo ""
    exit 1
fi

n=$1

if [ $n -lt 1 ]; then
    echo "n must be a positive integer."
    exit 1
fi

echo "The first $n digits of the Fibonacci series are:"

a=1
b=1

for (( i=0; i<n; i++ )); do
    echo "$a"
    temp=$a
    a=$b
    b=$((temp + b))
done

