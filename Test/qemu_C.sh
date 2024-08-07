#!/bin/bash

# set -x

# 将 SCC(standard CC) 替换为电脑上的交叉编译器 
SCC="arm-none-eabi-gcc-14"
QEMU="/home/zerosister/arm_v3/qemu/cwq_build/qemu-arm"
ARM_FLAGS="-cpu cortex-a7"
# 找到 arm 的 glibc 的 include 路径 和 lib 路径
COMPILE_FLAGS="-march=armv7 -mfpu=vfpv3"

# 检查是否传入了正确的参数个数
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 filename"
  exit 1
fi

FILE_PATH="$1"
cd "$FILE_PATH" || { echo "Error: cannot enter directory '$FILE_PATH'"; exit 1; }

# 设定目录路径
SY_DIR="./syFile"
C_DIR="./CFile"
IN_DIR="./input"
OUT_DIR="./tmpDir"
OUT_EXE_DIR="$OUT_DIR/exe"
OUT_Result_DIR="$OUT_DIR/result"
Lib_DIR="../lib"
Lib_File="$Lib_DIR/newlib.o"


# 确保输出目录存在
mkdir -p "$OUT_EXE_DIR"
mkdir -p "$OUT_Result_DIR"

# 遍历所有 .c 文件
for c_file in $C_DIR/*.c; do
  # 获取不带路径和拓展名的文件名
  filename=$(basename -- "$c_file")
  name="${filename%.*}"

  # 输入文件路径
  in_file="$IN_DIR/$name.in"

  # 输出文件路径
  out_exe="$OUT_EXE_DIR/$name"
  out_result="$OUT_Result_DIR/$name.qemuOut"

  # 编译为 .o 文件
  $SCC $COMPILE_FLAGS -c "$c_file"  -o "$out_exe.o"

  # 静态链接 .a 库
  # $SCC $COMPILE_FLAGS "$out_exe.o" -L "$Lib_DIR" -l:libsysy.a -o "$out_exe" 

  # 链接出问题，改用 sylib.o
  $SCC $COMPILE_FLAGS "$out_exe.o" "$Lib_File" -o "$out_exe"

  # 检查是否存在相应输入文件
  if [ -f "$in_file" ]; then
    $QEMU $ARM_FLAGS $out_exe < $in_file > "$out_result"
  else
    $QEMU $ARM_FLAGS $out_exe > "$out_result"
  fi

  rm "$out_exe.o" 
done

echo "所有文件处理完毕。"
