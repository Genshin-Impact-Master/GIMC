#!/bin/bash
set -x
# 检查是否传入了正确的参数个数
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 filename"
  exit 1
fi

FILE_PATH="$1"
cd "$FILE_PATH" || { echo "Error: cannot enter directory '$FILE_PATH'"; exit 1; }

mkdir -p syFile
for sy_file in ./*.sy; do
  [ -e "$sy_file" ] && mv "$sy_file" ./syFile/
done

mkdir -p stdOut
for out in ./*.out; do
  [ -e "$out" ] && mv "$out" ./stdOut/
done

mkdir -p input
for in_file in ./*.in; do
  [ -e "$in_file" ] && mv "$in_file" ./input/
done
echo "所有程序处理完毕"