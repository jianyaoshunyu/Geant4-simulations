#!/bin/bash

# Define the root directory to search
root_dir="./brem"

# Find all files and directories in the root directory and its subdirectories
find "$root_dir" -depth -print0 | while read -d $'\0' file
do
    # Replace "Z1" with an empty string in file and directory names
    new_file=$(echo "$file" | sed 's/Z1//g')
    if [ "$file" != "$new_file" ]; then
        mv -v "$file" "$new_file"
    fi

    # Replace "Z1" with an empty string in file contents
    if [ -f "$new_file" ]; then
        sed -i 's/Z1//g' "$new_file"
    fi
done
