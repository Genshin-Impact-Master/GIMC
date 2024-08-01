#include "../include/IR/IRBuilder.h"
#define GET_CNT_NAME "_" + std::to_string(parent->getCnt())
USING_GIMC_NAMESPACE

/* C 语言实现可变参数 格式化输出字符串，弃用
void IRBuilder::IRTextDump(const char* format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(irout, format, args); // 不能写入流中 类型需要 FILE*
  va_end(args);
}
*/


Module* IRBuilder::createModule(const std::string &name,
                                baseTypePtr type,
                                std::vector<GlobalVar*> globalVars,
                                std::vector<Function*> funcDefs,
                                std::vector<Function*> funcDeclares) {
    Module* module = new Module(name, type, globalVars, funcDefs, funcDeclares);
    return module;
}

Function* IRBuilder::createFunction(const std::string &fName, baseTypePtr ftype, std::vector<baseTypePtr> &arguTypes) {
  Function* function = new Function(fName, ftype, arguTypes);
  chosedFunc_ = function;
  return function;
}

template<>
GlobalVar* IRBuilder::createGlobalVar<Value*>(const std::string &name, baseTypePtr type, Value* values) {
  std::vector<Value*> vector;
  vector.push_back(values);
  return new GlobalVar(name, type, vector);
}

template<>
GlobalVar* IRBuilder::createGlobalVar<std::vector<Value*>>(const std::string &name, baseTypePtr type, std::vector<Value*> values) {
  return new GlobalVar(name, type, values);
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
  return createBinaryInst(kind, GET_CNT_NAME, lhs, rhs, parent);
}

Instruction* IRBuilder::createAllocaInst(const std::string &name, baseTypePtr type, BBlock *parent) {
  parent = checkBlockParent(parent);
  Alloca *inst = new Alloca(name, type, parent);
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createAllocaInst(baseTypePtr type, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createAllocaInst(GET_CNT_NAME, type, parent);
}

Instruction* IRBuilder::createStoreInst(Value *input, Value *ptr, BBlock *parent) {
  parent = checkBlockParent(parent);
  Store *inst = new Store("anonimous", voidType, parent, input, ptr);
  // fprintf(stdout, "the input is %s \n", input->getTypeName().data());
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createLoadInst(const std::string &name, baseTypePtr type, Value *ptr, BBlock *parent) {
  parent = checkBlockParent(parent);
  baseTypePtr loadType = type;
  if (TypeBase::isPointer(type)) {
    loadType = std::static_pointer_cast<PointerType>(type)->getBaseType();
  }
  Load *inst = new Load(name, loadType, parent, ptr);
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createLoadInst(baseTypePtr type, Value *ptr, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createLoadInst(GET_CNT_NAME, type, ptr, parent);
}

Instruction* IRBuilder::createCallInst(const std::string &name, Function *func, std::vector<Value*> &argus, BBlock *parent) {
  parent = checkBlockParent(parent);
  // 因为 Function 的类型即为其返回类型
  Call *inst = new Call(name, func->getType(), parent, func, argus);
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createCallInst(Function *func, std::vector<Value*> &argus, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createCallInst(GET_CNT_NAME, func, argus, parent);
}

Instruction* IRBuilder::createRetInst(const std::string &name, Value *retValue, BBlock *parent) {
  parent = checkBlockParent(parent);
  Ret *inst = new Ret(name, retValue->getType(), parent, retValue);
  parent->addInst(inst);
  return inst;
}
  
Instruction* IRBuilder::createRetInst(Value *retValue, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createRetInst(GET_CNT_NAME, retValue, parent);
}

Instruction* IRBuilder::createIcmpInst(const std::string &name, ICondKind kind, Value *first, Value *second, BBlock *parent) {
  parent = checkBlockParent(parent);
  Icmp *inst = new Icmp(name, i1Type, parent, kind, first, second);
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createIcmpInst(ICondKind kind, Value *first, Value *second, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createIcmpInst(GET_CNT_NAME, kind, first, second, parent);
}

Instruction* IRBuilder::createFcmpInst(const std::string &name, FCondKind kind, Value *first, Value *second, BBlock *parent) {
  parent = checkBlockParent(parent);
  Fcmp *inst = new Fcmp(name, i1Type, parent, kind, first, second);
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createFcmpInst(FCondKind kind, Value *first, Value *second, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createFcmpInst(GET_CNT_NAME, kind, first, second, parent);
}

Instruction* IRBuilder::createBrInst(Value *cond, BBlock *ifTure, BBlock *ifFalse, BBlock *parent) {
  parent = checkBlockParent(parent);
  // 判断是否为无条件跳转，检查两块必须非空
  Br *inst;
  // 三个操作 Value* 除了 ifTrue 均为 nullptr 才表示无条件跳转
  if (ifTure && ifFalse == nullptr && cond == nullptr) {
    inst = new Br("anonymous", voidType, parent, nullptr, ifTure, nullptr);
  }
  else if(ifTure && ifFalse && cond) {
    inst = new Br("anonymous", voidType, parent, cond, ifTure, ifFalse);
  }
  else
    fprintf(stderr, "生成 Br 指令异常\n");
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createGEPInst(const std::string &name, Value *ptr, Value *offset, BBlock *parent) {
  parent = checkBlockParent(parent);
  std::shared_ptr<PointerType> type = std::static_pointer_cast<PointerType>(ptr->getType());
  GEP *inst = new GEP(name, type->getBaseType(), parent, ptr, offset);
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createGEPInst(Value *ptr, Value *offset, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createGEPInst(GET_CNT_NAME, ptr, offset, parent);
}

Instruction* IRBuilder::createInt2FpInst(const std::string &name, Value *i32, BBlock *parent) {
  parent = checkBlockParent(parent);
  Int2Fp *inst = new Int2Fp(name, floatType, parent, i32);  // 一定转换为 floatType
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createInt2FpInst(Value *i32, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createInt2FpInst(GET_CNT_NAME, i32, parent);
}

Instruction* IRBuilder::createFp2IntInst(const std::string &name, Value *fp, BBlock *parent) {
  parent = checkBlockParent(parent);
  Fp2Int *inst = new Fp2Int(name, i32Type, parent, fp);   // 一定转换为 i32
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createFp2IntInst(Value *i32, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createFp2IntInst(GET_CNT_NAME, i32, parent);
}

Instruction* IRBuilder::createZextInst(const std::string &name, baseTypePtr type, Value *proto, BBlock *parent) {
  parent = checkBlockParent(parent);
  Zext *inst = new Zext(name, type, parent, proto);
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createZextInst(baseTypePtr type, Value *proto, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createZextInst(GET_CNT_NAME, type, proto, parent);
}

Instruction* IRBuilder::createPhiInst(const std::string &name, baseTypePtr type, std::vector<Value*> argus, BBlock *parent) {
  parent = checkBlockParent(parent);
  Phi *inst = new Phi(name, type, parent, argus);
  parent->addInst(inst);
  return inst;
}

Instruction* IRBuilder::createPhiInst(baseTypePtr type, std::vector<Value*> argus, BBlock *parent) {
  parent = checkBlockParent(parent);
  return createPhiInst(GET_CNT_NAME, type, argus, parent);
}

/******************************************************************************/
/*                                生成 LLVM IR                                */
/*****************************************************************************/
void IRBuilder::emitIRModule(Module *module) {
  irout.close();
  irout = std::ofstream(module->getName() + ".ll");
  std::vector<GlobalVar*> &globalVars = module->globalVars_;
  std::vector<Function*> &defs = module->funcDefs_;
  std::vector<Function*> &declares = module->funcDeclares_;
  std::cout<< globalVars.size() << " " << defs.size() << " " << declares.size() <<std::endl;
  for (auto &var : globalVars) {
    irout << var->getFullName() << " = global " << var->getType()->getDetailName() << " " << var->getData() << std::endl;
  }
  for (auto &def : defs) {
    emitIRFuncDef(def); 
  }
  for (auto &delcare : declares) {
    emitIRFuncDecl(delcare); 
  }
}

void IRBuilder::emitIRFuncDef(Function *func) {
  if (func->getEntryBBlock() == nullptr) {
    fprintf(stdout, "请先设置函数入口基本块\n");
  }
  std::vector<baseTypePtr> &arguTypes = func->arguTypes_;
  std::vector<Value> &argus = func->getArgus();
  irout <<"define " << func->getTypeName() << " " << func->getFullName()
        << "(";
  for (int i = 0; i < static_cast<int>(arguTypes.size()) - 1; i++) {
    irout << arguTypes[i]->getName() << " " << argus[i].getFullName() << ",";
  }
  if (arguTypes.size() != 0) {
    irout << arguTypes.back()->getName() << " " << argus.back().getFullName();  
  }
  irout << ") {" << std::endl;

  INode<BBlock> *iterator = func->getBBlockList().getHeadPtr();
  while (!iterator->isEnd()) {
    iterator = iterator->getNext();
    emitIRBBlock(iterator->getOwner());
  }
  
  IRTextLineDump("}");
}

void IRBuilder::emitIRFuncDecl(Function *func) {
  std::vector<baseTypePtr> &arguTypes = func->arguTypes_;
  irout << "declare " << func->getTypeName() << " " << func->getFullName()
        << "(";
  // @C++_Learn 注意 vector 的 size() 函数返回的是无符号整型，需要转换为 int
  for (int i = 0; i < static_cast<int>(arguTypes.size() - 1); i++) {
    irout << arguTypes[i]->getName() << ",";
  }
  if (arguTypes.size() != 0) {
    irout << arguTypes.back()->getName();  
  }
  irout << ")" << std::endl;
}

void IRBuilder::emitIRBBlock(BBlock *bBlk) {
  // 由于 BBlock 中不需要带有前缀故只需要 getName()
  irout << bBlk->getName() << ":" << std::endl ;
  INode<Instruction> *iterator = bBlk->getInstList().getHeadPtr();
  while (!iterator->isEnd()) {
    iterator = iterator->getNext();
    emitIRInst(iterator->getOwner());
  }
}

void IRBuilder::emitIRInst(Instruction *inst) {
  // 二元指令
  if (inst->kind_ > InstKind::BinaryOPBegin && inst->kind_ < InstKind::BinaryOpEnd) {
    BinaryInst* i = dynamic_cast<BinaryInst*>(inst);
    irout << '\t' << i->getFullName() << " = " << INST_STRING << i->getTypeName() << " "
          << i->getLhs()->getFullName() << ", " << i->getRhs()->getFullName() << std::endl;
  }
  // alloca 指令
  else if (inst->kind_ == InstKind::Alloca) {
    Alloca *i = dynamic_cast<Alloca*>(inst);
    std::shared_ptr<PointerType> ptr = std::dynamic_pointer_cast<PointerType>(inst->getType()); 
    irout << '\t' << i->getFullName() << " = " << INST_STRING << ptr->getName()
          << ", i32 " << ptr->getArraySizeCnt() << std::endl; 
  }
  // store 指令
  else if (inst->kind_ == InstKind::Store) {
    Store *i = dynamic_cast<Store*>(inst);
    irout << "\tstore " << i->getInput()->getTypeName() << " " << i->getInput()->getFullName();
        irout << ", ptr " << i->getPtr()->getFullName()<< std::endl;
  }
  // load 指令
  else if (inst->kind_ == InstKind::Load) {
    Load *i = dynamic_cast<Load*>(inst);
    irout << '\t' << i->getFullName() << " = " << INST_STRING
          << i->getTypeName() << ", ptr " << i->getPtr()->getFullName()<< std::endl;
  }
  // call 指令
  else if (inst->kind_ == InstKind::Call) {
    Call *i = dynamic_cast<Call*>(inst);
    // 因为所有的 void Type 均使用 voidTyPtr，故直接检测
    if (i->getType() != voidType) {
      irout << '\t' << i->getFullName() << " = ";
    }
    else irout << '\t';
    irout << INST_STRING
          << i->getFunc()->getTypeName() << " " << i->getFunc()->getFullName() << "(";
    std::vector<Value*> &argus = i->getArgus();
    for (int i = 1; i < static_cast<int>(argus.size()) - 1; i++) {
      irout << argus[i]->getTypeName() << " " << argus[i]->getFullName() << ",";
    }
    if (argus.size() != 1) {
      irout << argus.back()->getTypeName() << " " << argus.back()->getFullName();  
    }
    irout << ")" << std::endl;
  }
  // ret 指令
  else if (inst->kind_ == InstKind::Ret) {
    Ret *i = dynamic_cast<Ret*>(inst);
    irout << '\t' << INST_STRING << i->getTypeName() << " ";
    if (!TypeBase::isVoid(i->getType())) {
      irout << i->getRetValue()->getFullName();
    }
    irout << std::endl;;
  }
  // icmp 指令
  else if (inst->kind_ == InstKind::Icmp) {
    Icmp *i = dynamic_cast<Icmp*>(inst);
    irout << '\t' << i->getFullName() << " = " << INST_STRING << ST_IConds[static_cast<int>(i->ckind_.iCond)]
          << i->getFirst()->getTypeName() << " " << i->getFirst()->getFullName() << ", " << i->getSecond()->getFullName() << std::endl; 
  } 
  // fcmp 指令
  else if (inst->kind_ == InstKind::Fcmp) {
    Fcmp *i = dynamic_cast<Fcmp*>(inst);
    irout << '\t' << i->getFullName() << " = " << INST_STRING << ST_FConds[static_cast<int>(i->ckind_.fCond)]
          << i->getFirst()->getTypeName() << " " << i->getFirst()->getFullName() << ", " << i->getSecond()->getFullName() << std::endl; 
  }
  // Br 指令
  else if (inst->kind_ == InstKind::Br) {
    Br *i = dynamic_cast<Br*>(inst);
    irout << '\t' << INST_STRING;
    if (!i->isUnconditional()) {
      // 有条件跳转
      Value *cond = i->getCond();
      irout << cond->getTypeName() << " " << cond->getFullName() << ", label "
            << i->getTrueBBlk()->getFullName() << ", label " << i->getFalseBBlk()->getFullName() << std::endl; 
    }
    else {
      // 无条件跳转
      irout << "label " << i->getTrueBBlk()->getFullName() << std::endl;
    }
  }
  // GEP 指令
  else if (inst->kind_ == InstKind::GEP) {
    GEP *i = dynamic_cast<GEP*>(inst);
    Value *ptr = i->getPtr();
    ConstIntValue *offset = dynamic_cast<ConstIntValue*>(i->getOffsetValue());
    irout << '\t' << inst->getFullName() << " = getelementptr inbounds " << ptr->getType()->getDetailName()
          << ", ptr " << ptr->getFullName() << ", " << AddrLenPtr->getName() << " 0, " 
          << AddrLenPtr->getName() << " " << std::to_string(offset->getInt()) << std::endl;
  }
  // Int2Fp | Fp2Int 指令
  else if (inst->kind_ == InstKind::Int2Fp || inst->kind_ == InstKind::Fp2Int) {
    Instruction *i = dynamic_cast<Int2Fp*>(inst);
    if (i == nullptr) {
      i = dynamic_cast<Fp2Int*>(inst);
    }
    Value *i32 = i->ops_[0];
    irout << '\t' << i->getFullName() << " = " << INST_STRING << i32->getTypeName() << " " 
          << i32->getFullName() << " to " << i->getTypeName() << std::endl; 
  }
  else if (inst->kind_ == InstKind::Zext) {
    Zext *i = dynamic_cast<Zext*>(inst);
    Value *proto = i->getProto();
    irout << '\t' << i->getFullName() << " = " << INST_STRING << proto->getTypeName()
          << proto->getFullName() << " to " << i->getTypeName() << std::endl; 
  }
  else if (inst->kind_ == InstKind::Phi) {
    Phi *i = dynamic_cast<Phi*>(inst);
    irout << '\t' << i->getFullName() << " = " << INST_STRING << i->getTypeName() << " ";
    std::vector<Value*> &ops = i->getOps();
    int size = static_cast<int>(ops.size());
    for (int k = 1; k < size - 2; k += 2) {
      irout << "[" << ops[k]->getFullName() << ", " << ops[k+1]->getFullName() << "], ";
    }
    for (int k = size - 2; k < size; k += 2) {
      irout << "[" << ops[k]->getFullName() << ", " << ops[k+1]->getFullName() << "]" << std::endl;
    }
  }
}