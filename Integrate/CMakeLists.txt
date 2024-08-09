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
  ../include/LIR/codegen/ToLir.h
  ../include/LIR/lirInst/LirInst.h
  ../include/LIR/lirInst/LirInstMove.h
  ../include/LIR/lirInst/LirBinary.h
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
  ../include/LIR/LirHearders.h
  ../include/LirPass/RegAllocStack.h
  ../include/LirToArm/LirToArm.h
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
  ../LIR/codegen/ToLir.cpp
  ../LIR/lirInst/LirBinary.cpp
  ../LIR/lirInst/LirInstMove.cpp
  ../LIR/lirInst/LirInst.cpp
  ../LIR/lirOperand/Addr.cpp
  ../LIR/lirOperand/FImm.cpp
  ../LIR/lirOperand/FPhyReg.cpp
  ../LIR/lirOperand/FVReg.cpp
  ../LIR/lirOperand/IImm.cpp
  ../LIR/lirOperand/IPhyReg.cpp
  ../LIR/lirOperand/IVReg.cpp
  ../LIR/lirOperand/Imm.cpp
  ../LIR/lirOperand/Reg.cpp
  ../LIR/lirOperand/lirOperand.cpp
  ../LIR/lirVisitor/LirBlock.cpp
  ../LIR/lirVisitor/LirFunction.cpp
  ../LirPass/RegAllocStack.cpp
  ../LirToArm/LirToArm.cpp
  main.cpp
)
