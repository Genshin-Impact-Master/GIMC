# cmake 最低版本号
cmake_minimum_required( VERSION 3.10.0 )

# 比赛要求使用 clang-10.0.0 版本
set(CMAKE_CXX_COMPILER "clang++")

# 项目名称
project( GIMC CXX)

# 可执行文件 gimc_arm 的依赖文件
add_executable(gimc_arm
  ../include/Config.h
  ../include/LIR/codegen/ToLir.h
  ../include/LIR/lirInst/LirBinary.h
  ../include/LIR/lirInst/LirInst.h
  ../include/LIR/lirInst/LirInstMove.h
  ../include/LIR/lirOperand/Addr.h
  ../include/LIR/lirOperand/FImm.h
  ../include/LIR/lirOperand/FPhyReg.h
  ../include/LIR/lirOperand/FVReg.h
  ../include/LIR/lirOperand/IImm.h
  ../include/LIR/lirOperand/IPhyReg.h
  ../include/LIR/lirOperand/IVReg.h
  ../include/LIR/lirOperand/Imm.h
  ../include/LIR/lirOperand/Reg.h
  ../include/LIR/lirOperand/lirOperand.h
  ../include/LIR/visitor/LirBlock.h
  ../include/LIR/visitor/LirFunction.h
  ../include/LIR/visitor/LirModule.h
  ../include/LirToArm/LirToArm1.h
  ../Config.cpp
  example.cpp
  LirToArm1.cpp
)

# 可执行文件 gimc 的依赖文件
# @todo 基建搭好后使用
# add_executable(gimc
# )

# 编译参数
# SET( CMAKE_CXX_FLAGS "--std=c++17 -O2 -lm ")
# 先支持调试
SET( CMAKE_CXX_FLAGS "--std=c++17 -g -lm")

# 增加 graphviz 动态链接库
target_link_libraries(gimc_arm -lgvc -lcgraph -lcdt)

# build 目录位置
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/build)