#ifndef IRBUILDER_H_
#define IRBUILDER_H_

#include "../Config.h"
#include "Function.h"
#include "Inst.h"
#include "BBlock.h"
#include <cassert>
#include <fstream>
#include <string>
#include <cstdarg>
#include <cstdio>

GIMC_NAMESPACE_BEGIN

class Instruction;
class BinaryInst;
class Function;
class BBlock;
enum class InstKind;

/*
* 用于构建 IR 指令（用于添加类型检查等），产生 LLVM IR 文本
*/
class IRBuilder {
private:
  std::ofstream irout;          // 输出的 llvm IR 文件
  Function* chosedFunc_;         // 当前正在构造的函数 
  BBlock* chosedBBlock_;         // 当前正在构造的基本块

public:
  IRBuilder(const std::string outFileName, Function* chosedFunc, BBlock* chosedBBlock) : 
            irout(outFileName), chosedFunc_(chosedFunc), chosedBBlock_(chosedBBlock) {}

  IRBuilder() : IRBuilder("tmp_outputIR.ll", nullptr, nullptr) {}

/******************************************************************************/
/*                                创建 IR 数据结构                             */
/*****************************************************************************/

  // 创建 Function，并将创建的 Function 作为 chosedFunc 
  Function* createFunction(const std::string &fName, baseTypePtr fType);

  /**
   * 创建 BBlock
   * @param type 基本块的数据类型（可设为 VoidType）
   * @param parent 要插入的方程，默认为上次使用该 IRBuilder 创建的 Function*
  */
  BBlock* createBBlock(const std::string &name, baseTypePtr type, Function *parent = nullptr);

  /**
   * 创建二元运算指令
   * @param lhs 左操作数指针
   * @param rhs 右操作数指针
   * @param parent 要插入的基本块，默认为上次使用该 IRBuilder 创建的 BBlock*
  */
  Instruction* createBinaryInst(InstKind kind,
                                const std::string &name,
                                Value *lhs,
                                Value *rhs,
                                BBlock* parent = nullptr);

  Instruction* createBinaryInst(InstKind kind, Value *lhs, Value *rhs, BBlock* parent = nullptr);

  BBlock* checkBlockParent(BBlock* parent);

/******************************************************************************/
/*                                生成 LLVM IR                                */
/*****************************************************************************/
  
  // llvm 文本输出
  void IRTextDump(const std::string &llvmText) {
    irout << llvmText;
  }

  // llvm 文本输出带换行符
  void IRTextLineDump(const std::string &llvmText) {
    IRTextDump(llvmText);
    irout << '\n';
  }

  // 关闭输出文件
  void close() {irout.close();}

  // 生成 llvm IR 格式 Function
  void emitIRFunc(Function *func);

  // 生成 llvm IR 格式 BBlock
  void emitIRBBlock(BBlock *bBlk);

  // 生成 llvm IR 格式 Inst
  void emitIRInst(Instruction *Inst);

/******************************************************************************/
/*                                IRBuilder 通用工具                           */
/*****************************************************************************/
  
  bool isBinaryOp(InstKind kind) {
    return kind > InstKind::BinaryOPBegin && kind < InstKind::BinaryOpEnd;
  }
};

GIMC_NAMESPACE_END

#endif  //IRBUILDER_H_