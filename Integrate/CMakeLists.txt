cmake_minimum_required(VERSION 3.16)
# 比赛要求使用 clang-10.0.0 版本
set(CMAKE_CXX_COMPILER "clang++")
# 项目名称
project( GIMC CXX)
set(CMAKE_CXX_STANDARD 17)
SET( CMAKE_CXX_FLAGS "--std=c++17 -g -lm")
enable_testing()


add_executable(compiler
../LIR/codegen/ToLir.cpp
../LIR/lirInst/LirBinary.cpp
../LIR/lirInst/LirInstMove.cpp
../LIR/lirInst/LirInst.cpp
../LIR/lirOperand/lirOperand.cpp
../LIR/lirOperand/IVReg.cpp
../LIR/lirOperand/IImm.cpp
../LIR/lirOperand/Addr.cpp
../LIR/lirOperand/FVReg.cpp
../LIR/lirOperand/Reg.cpp
../LIR/lirOperand/Imm.cpp
../LIR/lirOperand/FImm.cpp
../LIR/lirOperand/IPhyReg.cpp
../LIR/lirOperand/FPhyReg.cpp
../LIR/lirVisitor/LirFunction.cpp
../LIR/lirVisitor/LirBlock.cpp
../LirPass/RegAllocStack.cpp
../IR/Type.cpp
../IR/ConstValue.cpp
../IR/Function.cpp
../IR/GlobalVar.cpp
../IR/IRBuilder.cpp
../IR/example.cpp
../IR/libsysy.c
../IR/BBlock.cpp
../IR/Value.cpp
../IR/Module.cpp
../IR/Inst.cpp
../parser/parser.cpp
../parser/parser.hpp
../Config.cpp
../lexer/lex.cpp
../semantic/genIR.cpp
../semantic/genIR.hpp
../include/AST.hpp
../include/LIR/codegen/ToLir.h
../include/LIR/LirHearders.h
../include/LIR/visitor/LirModule.h
../include/LIR/visitor/LirFunction.h
../include/LIR/visitor/LirBlock.h
../include/LIR/lirInst/LirBinary.h
../include/LIR/lirInst/LirInst.h
../include/LIR/lirInst/LirInstMove.h
../include/LIR/lirOperand/Imm.h
../include/LIR/lirOperand/lirOperand.h
../include/LIR/lirOperand/IVReg.h
../include/LIR/lirOperand/Addr.h
../include/LIR/lirOperand/FVReg.h
../include/LIR/lirOperand/IImm.h
../include/LIR/lirOperand/FImm.h
../include/LIR/lirOperand/IPhyReg.h
../include/LIR/lirOperand/Reg.h
../include/LIR/lirOperand/FPhyReg.h
../include/LirPass/RegAllocStack.h
../include/IR/ConstValue.h
../include/IR/Inst.h
../include/IR/Value.h
../include/IR/libsysy.h
../include/IR/GlobalVar.h
../include/IR/Module.h
../include/IR/Function.h
../include/IR/Type.h
../include/IR/IRBuilder.h
../include/IR/BBlock.h
../include/Define.hpp
../include/Config.h
../include/Token.hpp
../include/Pass/Pres_Succs_Calculate.h
../include/Pass/PassManager.h
../include/Pass/Mem2reg.h
../include/Pass/Domination.h
../include/SymbolTable.hpp
../include/LirToArm/LirToArm.h
../include/Utils/ErrorConfig.h
../include/Utils/BiMap.h
../include/Utils/IList.h
main.cpp
check.cpp
../Pass/Mem2reg.cpp
../Pass/PassManager.cpp
../Pass/Domination.cpp
../Pass/Pres_Succs_Calculate.cpp
../LirToArm/LirToArm.cpp
)
