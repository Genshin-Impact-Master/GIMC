cmake_minimum_required(VERSION 3.16)
# 比赛要求使用 clang-10.0.0 版本
set(CMAKE_CXX_COMPILER "clang++")
# 项目名称
project( GIMC CXX)
set(CMAKE_CXX_STANDARD 17)
SET( CMAKE_CXX_FLAGS "--std=c++17 -g -lm")
enable_testing()


add_executable(compiler
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
  ../semantic/genIR.cpp
  ../IR/IRBuilder.cpp
  ../IR/Value.cpp
  ../parser/parser.cpp
  ../parser/parser.hpp
  ../lexer/lex.cpp
  main.cpp
)
