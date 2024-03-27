#!/bin/bash

integer_list=()
non_integer_list=()

for arg in "$@"; do
  if [[ "$arg" =~ ^[+-]?[0-9]+$ ]]; then
    integer_list+=("$arg")
  else
    non_integer_list+=("$arg")
  fi
done

echo "List of Integers:"
for integer in "${integer_list[@]}"; do
  echo "$integer"
done

echo "List of Non-Integers:"
for non_integer in "${non_integer_list[@]}"; do
  echo "$non_integer"
done

