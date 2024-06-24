#!/bin/bash

# 检查是否传入跳过 make 的参数
skip_make=false
for arg in "$@"; do
  if [ "$arg" == "-skip" ]; then
    skip_make=true
    break
  fi
done

# 如果没有跳过 make，执行清理和编译
if [ ${skip_make} = false ]; then
  # 如果文件夹存在
  # if [ -d ../build ]; then
  #   rm -rf ../build
  # fi

  cd ../
  cmake -Bbuild
  cd build
  make
  ./gimc_ir
else 
  echo "Skipping make..."
  cd ../build
  ./gimc_ir
fi

# 遍历 ../build 目录下的所有 .ll 文件
for example in ./example*.ll; do 
  echo "Combining ${example} with lib.ll..."
  
  # 链接 .ll 文件和 lib.ll
  llvm-link ${example} ../IR/lib.ll -S -o out.ll
  
  # 获取文件名 （不含路径与后缀）
  basename=$(basename "${example}" .ll)

  # 编译生成可执行文件
  clang++ out.ll -o "../build/${basename}.out"

  # 删除中间的 out.ll
  # rm out.ll
done
echo 
echo "get all example*.out in build/"

# 清理工作
# for tmp in ../IR/tmp*; do
#   rm ${tmp}
# done

