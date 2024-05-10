#include "../include/IR/IRBuilder.h"
USING_GIMC_NAMESPACE

/* C 语言实现可变参数 格式化输出字符串，弃用
void IRBuilder::IRTextDump(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(irout, format, args); // 不能写入流中 类型需要 FILE*
  va_end(args);
}
*/

Function* IRBuilder::createFunction(const std::string &fName, baseTypePtr ftype) {
  Function* function = new Function(fName, ftype);
  chosedFunc_ = function;
  return function;
}

BBlock* IRBuilder::createBBlock(const std::string &name, baseTypePtr type, Function* parent) {
  // 在创建 BBlock 前未创建函数
  if (parent == nullptr && chosedFunc_ == nullptr) {
    fprintf(stderr, "请先调用 createFunction 构造一个函数\n");
    return nullptr;
  }

  else if (parent == nullptr) parent = chosedFunc_;

  BBlock* bBlk = new BBlock(name, type, parent);
  chosedBBlock_ = bBlk;
  parent->addBBlock(bBlk);
  return bBlk;
}

BBlock* IRBuilder::checkBlockParent(BBlock* parent){
  // 在创建 Instruction 前未创建 BBlock
  if (parent == nullptr && chosedBBlock_ == nullptr) {
    fprintf(stderr, "请先调用 createBBlock 构造一个基本块\n");
    return nullptr;
  }
  else if (parent == nullptr) parent = chosedBBlock_;
  return parent;
}

/**
 * @todo 需要检查左右 Value 的类型必须一致
*/
Instruction* IRBuilder::createBinaryInst(InstKind kind, const std::string &name, Value *lhs, Value *rhs, BBlock* parent) {
  parent = checkBlockParent(parent);
  if (!isBinaryOp(kind)) { 
    fprintf(stderr, "%s 指令并非 二元操作指令", ST_Insts[static_cast<int>(kind)].c_str());
    return nullptr;
  }
  BinaryInst *inst = new BinaryInst(name, lhs->getType(), kind, parent, lhs, rhs);
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createBinaryInst(InstKind kind, Value *lhs, Value *rhs, BBlock* parent) {
  parent = checkBlockParent(parent);
  return createBinaryInst(kind, std::to_string(parent->getCnt()), lhs, rhs, parent);
}

/******************************************************************************/
/*                                生成 LLVM IR                                */
/*****************************************************************************/
void IRBuilder::emitIRFunc(Function *func) {
  IRTextDump("define ");
  IRTextLineDump(func->getType()->getName()
                         + " @" + func->getName() +"() {");
  for (auto bBlkPtr : func->bBlocks) {
    emitIRBBlock(bBlkPtr);
  }
  IRTextLineDump(std::string("\t") + "ret i32 %3");
  IRTextLineDump("}");
}

void IRBuilder::emitIRBBlock(BBlock *bBlk) {
  irout << bBlk->getName() << ":\n" ;
  for (auto inst : bBlk->instructions) {
    emitIRInst(inst);
  }
}

void IRBuilder::emitIRInst(Instruction *inst) {
  if (inst->kind_ > InstKind::BinaryOPBegin && inst->kind_ < InstKind::BinaryOpEnd) {
    BinaryInst* i = dynamic_cast<BinaryInst*>(inst);
    irout << '\t' << i->getFullName() << "=" << ST_Insts[static_cast<int>(i->kind_)] << " " << i->getTypeName() << " "
        << i->lhs_->getFullName() << ", " << " " << i->rhs_->getFullName() << std::endl;
  }
}