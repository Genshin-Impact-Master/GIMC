#!/bin/bash

# 将 SCC(standard CC) 替换为电脑上的交叉编译器 
SCC="arm-suse-linux-gnueabi-gcc-14"

# 找到 arm 的 glibc 的 include 路径 和 lib 路径

# 设定目录路径
SY_DIR="./stdSY"
IN_DIR="./input"
OUT_DIR="./stdOut"

# 确保输出目录存在
mkdir -p $OUT_DIR

# 循环遍历所有 .sy 文件
for sy_file in $SY_DIR/*.sy; do
    # 获取不带路径和扩展名的文件名
    filename=$(basename -- "$sy_file")
    name="${filename%.*}"

    # 输入文件路径
    in_file="$IN_DIR/$name.in"
    
    # 输出文件路径
    out_file="$OUT_DIR/$name.stdOut"
    
    # # 检查是否存在相应的输入文件
    # if [ -f "$in_file" ]; then
    #     # 输入
    #     $SCC "$sy_file sylib.o" < "$in_file" > "$out_file"
    # else
    #     # 仅编译执行
    #     $SCC "$sy_file sylib.o" > "$out_file"
    # fi
done

echo "所有文件处理完毕。"
