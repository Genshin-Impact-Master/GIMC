#!/bin/bash

# 检查是否传入了目标文件夹作为参数
if [ $# -ne 1 ]; then
    echo "Usage: $0 path/to/your/folder"
    exit 1
fi

# 获取当前目录
current_dir=$(pwd)

# 获取目标文件夹路径
target_folder=$1

# 检查目标文件夹是否存在
if [ ! -d "$target_folder" ]; then
    echo "Error: The specified folder does not exist."
    exit 1
fi

# 列出目标文件夹中的所有文件及其相对路径
find "$target_folder" -type f | while read -r file; do
    # 获取相对于当前目录的相对路径
    relative_path=$(realpath --relative-to="$current_dir" "$file")

    echo "$relative_path"
done
