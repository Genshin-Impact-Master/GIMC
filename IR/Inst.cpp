#include "../include/IR/Inst.h"
#include <iostream>

USING_GIMC_NAMESPACE

Instruction::Instruction(const std::string &name,
                         baseTypePtr type,
                         InstKind kind,
                         BBlock *parent) : Value(name, type), kind_(kind), parent_(parent), instNode_(INode<Instruction>(nullptr, nullptr, this)) {}

Instruction::Instruction(baseTypePtr type, InstKind kind, BBlock *parent) :
                         Instruction(std::to_string(parent->getCnt()),
                                     type, kind, parent) {}

Instruction::Instruction(InstKind kind, BBlock *parent) : Instruction(i32Type, kind, parent) {}

Instruction::Instruction(const std::string &name, InstKind kind, BBlock *parent) :
                         Instruction(name, i32Type, kind, parent) {}

void Instruction::calculateDef_Uses() {
  for (auto op : ops_) {
    op->getUses().push_back(this);
  }
}

BinaryInst::BinaryInst(const std::string &name,
                        baseTypePtr type,
                        InstKind kind,
                        BBlock *parent,
                        Value *lhs,
                        Value *rhs)
                        : Instruction(name, type, kind, parent) {
                          ops_.push_back(lhs);
                          ops_.push_back(rhs);
                          calculateDef_Uses();
                        }

Store::Store(const std::string &name,
              baseTypePtr type,
              BBlock *parent,
              Value *input,
              Value *ptr) : Instruction(name, type, InstKind::Store, parent) {
                ops_.push_back(input);
                ops_.push_back(ptr);
                calculateDef_Uses();
              } 

Load::Load(const std::string &name,
            baseTypePtr type,
            BBlock *parent,
            Value *ptr) : Instruction(name, type, InstKind::Load, parent){
              ops_.push_back(ptr);
              calculateDef_Uses();
            }

Call::Call(const std::string &name,
            baseTypePtr type,
            BBlock *parent,
            Function *func,
            std::vector<Value*> &argus) : Instruction(name, type, InstKind::Call, parent) {
              ops_.push_back(func);
              for (auto argu : argus) {
                ops_.push_back(argu);
              }
              calculateDef_Uses();
            }

Ret::Ret(const std::string &name,
          baseTypePtr type,
          BBlock *parent,
          Value* retValue) : Instruction(name, type, InstKind::Ret, parent) {
            ops_.push_back(retValue);
            calculateDef_Uses();
          }

Icmp::Icmp(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      ICondKind kind,
      Value *first,
      Value *second) : Instruction(name, type, InstKind::Icmp, parent) {
        ckind_.iCond = kind;
        ops_.push_back(first);
        ops_.push_back(second);
        calculateDef_Uses();
      }

Fcmp::Fcmp(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      FCondKind kind,
      Value *first,
      Value *second) : Instruction(name, type, InstKind::Fcmp, parent) {
        ckind_.fCond = kind;
        ops_.push_back(first);
        ops_.push_back(second);
        calculateDef_Uses();
      }

Br::Br(const std::string &name,
        baseTypePtr type,
        BBlock *parent,
        Value *cond,
        BBlock *ifTrue,
        BBlock *ifFalse) : Instruction(name, type, InstKind::Br, parent) {
          if (cond != nullptr)
            ops_.push_back(cond);
          ops_.push_back(ifTrue);
          if (ifFalse != nullptr)
            ops_.push_back(ifFalse);
          calculateDef_Uses();
        }

bool Br::isUnconditional() {
  if (ops_.size() == 1)
    return true;
  else if(ops_.size() == 3)
    return false;
  fprintf(stderr, "Br 指令参数异常\n");
  exit(1);
}

GEP::GEP(const std::string &name,
          baseTypePtr type,
          BBlock *parent,
          Value *ptr,
          int offset) : Instruction(name, type, InstKind::GEP, parent) {
            ops_.push_back(ptr);
            ops_.push_back(new ConstIntValue(AddrLenPtr, offset));
            calculateDef_Uses();
          }

Fp2Int::Fp2Int(const std::string &name,
                baseTypePtr type,
                BBlock *parent,
                Value *fp) : Instruction(name, type, InstKind::Fp2Int, parent) {
                  // 对于类型检查
                  if (!TypeBase::isFloat(fp->getType())) {
                    // 若 fp 的类型非浮点数
                    fprintf(stderr, "Not a float!\n");
                    exit(1);
                  }
                  ops_.push_back(fp);
                  calculateDef_Uses();
                }

Int2Fp::Int2Fp(const std::string &name,
                baseTypePtr type,
                BBlock *parent,
                Value *i32) : Instruction(name, type, InstKind::Int2Fp, parent) {
                  // 对于类型检查
                  if (!TypeBase::isInteger(i32->getType())) {
                    // 若 i32 的类型非整数
                    fprintf(stderr, "Not a int!\n");
                    exit(1);
                  }
                  ops_.push_back(i32);
                  calculateDef_Uses();
                }

Phi::Phi(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      std::vector<Value*> maps) : Instruction(name, type, InstKind::Phi, parent) {
        for (auto map : maps) {
          ops_.push_back(map);
        }
        calculateDef_Uses();
        std::cout << "新建的 phi 指令是 " << ops_[0]->getFullName() << " 的 phi 结点" << std::endl; 
      }