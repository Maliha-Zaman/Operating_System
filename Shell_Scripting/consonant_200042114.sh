#!/bin/bash

read -p "Enter an input string: " input_string

output_string=""

for (( i=0; i<${#input_string}; i++ )); do
    char="${input_string:$i:1}"
    if [[ "$char" != [aeiouAEIOU] ]]; then
        output_string="${output_string}${char}"
    fi
done

echo "$output_string"

