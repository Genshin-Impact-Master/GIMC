# cmake 最低版本号
cmake_minimum_required( VERSION 3.10.0 )

# 比赛要求使用 clang-10.0.0 版本
set(CMAKE_CXX_COMPILER "clang++")

# 项目名称
project( GIMC CXX)

# 可执行文件 gimc_ir 的依赖文件
add_executable(gimc_ir
  IR/BBlock.h
  IR/ConstValue.h
  IR/Function.h
  IR/Inst.h
  IR/IRBuilder.h
  IR/Type.h
  IR/Value.h
  Utils/ErrorConfig.h
  Config.h
  IR/BBlock.cpp
  IR/Function.cpp
  IR/ConstValue.cpp
  IR/Inst.cpp
  IR/Type.cpp
  IR/example.cpp
  IR/IRBuilder.cpp
  IR/Value.cpp
)

# 可执行文件 gimc 的依赖文件
# @todo 基建搭好后使用
# add_executable(gimc
# )

# 编译参数
SET( CMAKE_CXX_FLAGS "--std=c++17 -O2 -lm")

# build 目录位置
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)