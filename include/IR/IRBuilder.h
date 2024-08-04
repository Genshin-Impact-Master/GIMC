#ifndef IRBUILDER_H_
#define IRBUILDER_H_
#define INST_STRING ST_Insts[static_cast<int>(i->kind_)]      // 方便打印相应的 Inst

#include "../Config.h"
#include "Module.h"
#include "GlobalVar.h"
#include "Function.h"
#include "Inst.h"
#include "BBlock.h"
#include "Type.h"
#include <cassert>
#include <fstream>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <iostream>

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

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

  /**
   * 创建 Module
  */
  Module* createModule(const std::string &name,
                        baseTypePtr type,
                        std::vector<GlobalVar*> globalVars,
                        std::vector<Function*> funcDefs,
                        std::vector<Function*> funcDeclares);

  // 不带参数版本 Module
  Module *createModule(const std::string &name,
                        baseTypePtr type) {return new Module(name, type);}

  // 创建 Function，并将创建的 Function 作为 chosedFunc 
  Function* createFunction(const std::string &fName, baseTypePtr fType, std::vector<baseTypePtr> &arguTypes);

  /**
   * @note 泛型编程，方便创建数组或常量元素
   * @brief 创建全局变量 GlobalVar
   * @param type 为创建的 Value 的类型（数组则为基本类型）
  */
  template<typename T>
  GlobalVar* createGlobalVar(const std::string &name, baseTypePtr type, T values);
  /**
   * 创建 BBlock
   * @param type 基本块的数据类型（可设为 VoidType）
   * @param parent 要插入的方程，默认为上次使用该 IRBuilder 创建的 Function*
  */
  BBlock* createBBlock(const std::string &name, baseTypePtr type, Function *parent = nullptr);

  /**
   * 创建二元运算指令
   * @param lhs 左操作数指针，注意获得的 Value 的类型和左操作数的类型相同
   * @param rhs 右操作数指针
   * @param parent 要插入的基本块，默认为上次使用该 IRBuilder 创建的 BBlock*
  */
  Instruction* createBinaryInst(InstKind kind,
                                const std::string &name,
                                Value *lhs,
                                Value *rhs,
                                BBlock* parent = nullptr);
  Instruction* createBinaryInst(InstKind kind, Value *lhs, Value *rhs, BBlock *parent = nullptr);

  /**
   * 创建 alloca 指令
   * @param type 指针指向内存的基类
   * @param cnt 数组元素个数（非数组设置为 1）
  */
  Instruction* createAllocaInst(const std::string &name, baseTypePtr type, BBlock *parent = nullptr);
  Instruction* createAllocaInst(baseTypePtr type, BBlock *parent = nullptr);

  /**
   * 创建 store 指令
   * @param input 待存入的值指针
   * @param ptr   指针指向存入地址
  */
  Instruction* createStoreInst(Value *input, Value *ptr, BBlock *parent = nullptr);

  /**
   * 创建 load 指令
   * @param ptr 需要读取的内存的指针
  */
  Instruction* createLoadInst(const std::string &name, baseTypePtr type, Value *ptr, BBlock *parent = nullptr);
  Instruction* createLoadInst(baseTypePtr type, Value *ptr, BBlock *parent = nullptr);

  /**
   * 创建 call 指令，调用函数
   * 此条 Instruction 的 type 会设置为函数的返回类型（即 call 指令会产生一个函数返回值的 Value）
   * @see IR/IRBuilder.cpp
   * @param func 被调用的函数指针
  */
  Instruction* createCallInst(const std::string &name, Function *func, std::vector<Value*> &argus, BBlock *parent = nullptr);
  Instruction* createCallInst(Function *func, std::vector<Value*> &argus,BBlock *parent = nullptr);

  /**
   * 创建 ret 指令
  */
  Instruction* createRetInst(const std::string &name, Value *retValue, BBlock *parent = nullptr);
  Instruction* createRetInst(Value *retValue, BBlock *parent = nullptr);

  /**
   * 创建 icmp 指令 
  */
  Instruction* createIcmpInst(const std::string &name, ICondKind kind, Value *first, Value *second, BBlock *parent = nullptr);
  Instruction* createIcmpInst(ICondKind kind, Value *first, Value *second, BBlock *parent = nullptr);

  /**
   * 创建 fcmp 指令
   */
  Instruction* createFcmpInst(const std::string &name, FCondKind kind, Value *first, Value *second, BBlock *parent = nullptr);
  Instruction* createFcmpInst(FCondKind kind, Value *first, Value *second, BBlock *parent = nullptr);

  /**
   * 创建 Br 指令，Br 指令不需要名称
  */
  Instruction* createBrInst(Value *cond, BBlock *ifTure, BBlock *ifFalse, BBlock *parent = nullptr);

  /**
   * 创建 GEP 指令
   */
  Instruction* createGEPInst(const std::string &name, Value *ptr, Value *offset, BBlock *parent = nullptr);
  Instruction* createGEPInst(Value *ptr, Value *offset, BBlock *parent  = nullptr);
  Instruction* createGEPInst(const std::string &name, baseTypePtr type, Value *ptr, Value *offset, BBlock *parent = nullptr);
  Instruction* createGEPInst(baseTypePtr type, Value *ptr, Value *offset, BBlock *parent = nullptr);

  /**
   * @note 修改 GEP 指令为 形参模式
   * @param isParam 若为形参则设为 true
   * */
  void setGEPInst(Instruction *gep, bool isParam) {
    GEP *inst = dynamic_cast<GEP*>(gep);
    if (!inst) {
      error("setGEPInst gep 实际类型必须为 GEP*");
    }
    inst->setIsParam(isParam);
  }

  /**
   * 创建 Fp2Int 指令
   */
  Instruction* createFp2IntInst(const std::string &name, Value *fp, BBlock *parent = nullptr);
  Instruction* createFp2IntInst(Value *fp, BBlock *parent = nullptr);

  /**
   * 创建 Int2Fp 指令
   */
  Instruction* createInt2FpInst(const std::string &name, Value *i32, BBlock *parent = nullptr);
  Instruction* createInt2FpInst(Value *i32, BBlock *parent = nullptr);

  /**
   * 创建 Zext 指令
   */
  Instruction* createZextInst(const std::string &name, baseTypePtr type, Value *proto, BBlock *parent = nullptr);
  Instruction* createZextInst(baseTypePtr type, Value *proto, BBlock *parent = nullptr);

  /**
   * 创建 Phi 指令
   * @param type 创建的 phi 指令注意类型为实际的数据类型而非变量指针 ptr
   */
  Instruction* createPhiInst(const std::string &name, baseTypePtr type, std::vector<Value*> argus, BBlock *parent = nullptr);
  Instruction* createPhiInst(baseTypePtr type, std::vector<Value*> argus, BBlock *parent = nullptr);

  /**
   * 创建 InitMem 指令
   */
  Instruction* createInitMemInst(const std::string &name, baseTypePtr type, Value *ptr, int length, BBlock *parent = nullptr);
  Instruction* createInitMemInst(baseTypePtr type, Value *ptr, int length, BBlock *parent = nullptr);

  /**
   * 检查是否存在 BBlock
  */
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

  // 生成 llvm IR 格式 Module
  void emitIRModule(Module *module);

  // 生成 llvm IR 格式 Function 的定义 define
  void emitIRFuncDef(Function *func);

  // 生成 llvm IR 格式 Function 的声明 declare
  void emitIRFuncDecl(Function *func);

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

  // 切换选中函数
  void setChosedFunc(Function *func) {chosedFunc_ = func;}
  // 切换选中基本块
  void setChosedBBlock(BBlock *bBlock) {chosedBBlock_ = bBlock;}
  // 获取当前正在构建的基本块
  BBlock* getChosedBBlk() {return chosedBBlock_;}
  // 获取当前正在构建的 Function
  Function* getChosedFunc() {return chosedFunc_;}

  void setEntry(BBlock *bBlk) {chosedFunc_->setEntry(bBlk);}

};

  template<>
  GlobalVar* IRBuilder::createGlobalVar<std::vector<Value*>>(const std::string &name, baseTypePtr type, std::vector<Value*> values);

  template<>
  GlobalVar* IRBuilder::createGlobalVar<Value*>(const std::string &name, baseTypePtr type, Value* values);
  

GIMC_NAMESPACE_END

#endif  //IRBUILDER_H_