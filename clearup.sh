#!/bin/bash

# Define the directories
IR_DIR="./IR"
PASS_DIR="./Pass"
INCLUDE_DIR="./include"

# Define the file patterns to delete
PATTERNS=("example[0-9]*.ll" "main.png" "tmp_outputIR.ll" "*.gch")

# Function to delete files matching patterns in a directory
delete_files() {
  local DIR=$1
  for PATTERN in "${PATTERNS[@]}"; do
    # Find and delete files matching the pattern in the directory
    find "$DIR" -name "$PATTERN" -exec rm -f {} +
  done
}

# Delete files in IR directory
delete_files "$IR_DIR"

# Delete files in Pass directory
delete_files "$PASS_DIR"

delete_files "$INCLUDE_DIR"

for dir in "$INCLUDE_DIR"; do  
    # 确保它是一个目录  
    if [[ -d "$dir" ]]; then  
        # 去除末尾的斜杠  
        dirname="${dir%/}"  
        # 假设你的操作是打印目录名  
        delete_files $dirname  
        # 在这里添加你的操作  
    fi  
done

echo "Deletion completed."
