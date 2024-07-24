#!/bin/bash

# Define the directories
IR_DIR="./IR"
PASS_DIR="./Pass"

# Define the file patterns to delete
PATTERNS=("example[0-9]*.ll" "main.png" "tmp_outputIR.ll")

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

echo "Deletion completed."
