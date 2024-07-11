# cmake 最低版本号
cmake_minimum_required( VERSION 3.10.0 )

# 比赛要求使用 clang-10.0.0 版本
set(CMAKE_CXX_COMPILER "clang++")

# 项目名称
project( GIMC CXX)

# 可执行文件 gimc_ir 的依赖文件
add_executable(gimc_ir
  ../include/IR/Module.h
  ../include/IR/GlobalVar.h
  ../include/IR/BBlock.h
  ../include/IR/ConstValue.h
  ../include/IR/Function.h
  ../include/IR/Inst.h
  ../include/IR/IRBuilder.h
  ../include/IR/Type.h
  ../include/IR/Value.h
  ../include/Utils/ErrorConfig.h
  ../include/Utils/IList.h
  ../include/Config.h
  ../Config.cpp
  ../IR/GlobalVar.cpp
  ../IR/Module.cpp
  ../IR/BBlock.cpp
  ../IR/Function.cpp
  ../IR/ConstValue.cpp
  ../IR/Inst.cpp
  ../IR/Type.cpp
  genIR.cpp
  ../IR/IRBuilder.cpp
  ../IR/Value.cpp
  ../parser/parser.cpp
  ../parser/parser.hpp
  ../lexer/lex.cpp
)

# 可执行文件 gimc 的依赖文件
# @todo 基建搭好后使用
# add_executable(gimc
# )

# 编译参数
# SET( CMAKE_CXX_FLAGS "--std=c++17 -O2 -lm ")
# 先支持调试
SET( CMAKE_CXX_FLAGS "--std=c++17 -g -lm ")

# build 目录位置
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)