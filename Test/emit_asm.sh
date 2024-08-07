#!/bin/bash
# 将 SCC(standard CC) 替换为电脑上的交叉编译器 
SCC="arm-none-eabi-gcc-14"
COMPILE_FLAGS="-march=armv7 -mfpu=vfpv3"

# 检查是否传入了正确的参数个数
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 filename"
  exit 1
fi

FILE_PATH="$1"
cd "$FILE_PATH" || { echo "Error: cannot enter directory '$FILE_PATH'"; exit 1; }

# 设定目录路径
C_DIR="./CFile"
OUT_DIR="./tmpDir"
OUT_ASM_DIR="$OUT_DIR/asm"

# 确保输出目录存在
mkdir -p "$OUT_ASM_DIR"

# 遍历所有 .c 文件
for c_file in $C_DIR/*.c; do
  # 获取不带路径和拓展名的文件名
  filename=$(basename -- "$c_file")
  name="${filename%.*}"

  $SCC $COMPILE_FLAGS $c_file -S -o "$OUT_ASM_DIR/$name.s"
  echo "输出 $name.s 到 $OUT_ASM_DIR"
done
echo "已输出所有 .s 文件"