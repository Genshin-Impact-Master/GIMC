#!/bin/bash
set -x
# 检查是否传入了正确的参数个数
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 filename"
  exit 1
fi

FILE_PATH="$1"
cd "$FILE_PATH" || { echo "Error: cannot enter directory '$FILE_PATH'"; exit 1; }

# 确保 syFile 目录存在
if [ ! -d "syFile" ]; then
  echo "Error: syFile directory does not exist."
  exit 1
fi

# 确保 CFile 目录存在，不存在则创建
mkdir -p CFile

# 遍历 syFile 目录下的所有 .sy 文件
for sy_file in syFile/*.sy; do
  if [ -f "$sy_file" ]; then
    # 获取不带路径和扩展名的文件名
    base_name=$(basename "$sy_file" .sy)
    # 临时文件的目标路径
    tmp_file="CFile/${base_name}.c"
    # 将 #include 语句写入临时文件
    echo '#include "../../lib/newlib.h"' > "$tmp_file"
    # 追加原始文件的内容到临时文件
    cat "$sy_file" >> "$tmp_file"
    echo "Processed file: $sy_file to $tmp_file"
  else
    echo "No .sy files found in syFile directory."
  fi
done

echo "所有文件处理完毕"

