#!/bin/bash


read -p "Enter the base directory name: " base_dir


mkdir -p "$base_dir"


read -p "Enter the name of the subdirectory: " subdir_name


mkdir -p "$base_dir/$subdir_name"


read -p "Enter the name of the file: " file_name

touch "$base_dir/$subdir_name/$file_name"

echo "Directory structure created successfully."

