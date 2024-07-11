#include "../include/IR/Inst.h"

USING_GIMC_NAMESPACE

Instruction::Instruction(const std::string &name,
                         baseTypePtr type,
                         InstKind kind,
                         BBlock *parent) : Value(name, type), kind_(kind), parent_(parent), instNode_(INode<Instruction>(nullptr, this)) {}

Instruction::Instruction(const std::string &name,
                         baseTypePtr type,
                         InstKind kind,
                         BBlock *parent,
                         std::vector<Value*> argus) : Value(name, type), kind_(kind), parent_(parent), argus_(argus), instNode_(INode<Instruction>(nullptr, this)) {}

Instruction::Instruction(const std::string &name,
                         baseTypePtr type,
                         InstKind kind,
                         BBlock *parent,
                         CondKind ckind) : Value(name, type), kind_(kind), parent_(parent), ckind_(ckind), instNode_(INode<Instruction>(nullptr, this)) {}

Instruction::Instruction(baseTypePtr type, InstKind kind, BBlock *parent) :
                         Instruction(std::to_string(parent->getCnt()),
                                     type, kind, parent) {}

Instruction::Instruction(InstKind kind, BBlock *parent) : Instruction(i32Type, kind, parent) {}

Instruction::Instruction(const std::string &name, InstKind kind, BBlock *parent) :
                         Instruction(name, i32Type, kind, parent) {}
                         
BinaryInst::BinaryInst(const std::string &name,
                        baseTypePtr type,
                        InstKind kind,
                        BBlock *parent,
                        Value *lhs,
                        Value *rhs)
                        : Instruction(name, type, kind, parent) {
                          ops_.push_back(lhs);
                          ops_.push_back(rhs);
                        }

Store::Store(const std::string &name,
              baseTypePtr type,
              BBlock *parent,
              Value *input,
              Value *ptr) : Instruction(name, type, InstKind::Store, parent) {
                ops_.push_back(input);
                ops_.push_back(ptr);
              } 

Load::Load(const std::string &name,
            baseTypePtr type,
            BBlock *parent,
            Value *ptr) : Instruction(name, type, InstKind::Load, parent){
              ops_.push_back(ptr);
            }

Call::Call(const std::string &name,
            baseTypePtr type,
            BBlock *parent,
            Function *func,
            std::vector<Value*> &argus) : Instruction(name, type, InstKind::Call, parent, argus) {
              ops_.push_back(func);
            }

Ret::Ret(const std::string &name,
          baseTypePtr type,
          BBlock *parent,
          Value* retValue) : Instruction(name, type, InstKind::Ret, parent) {
            ops_.push_back(retValue);
          }

Icmp::Icmp(const std::string &name,
      baseTypePtr type,
      BBlock *parent,
      CondKind kind,
      Value *first,
      Value *second) : Instruction(name, type, InstKind::Icmp, parent, kind) {
        ops_.push_back(first);
        ops_.push_back(second);
      }

Br::Br(const std::string &name,
        baseTypePtr type,
        BBlock *parent,
        Value *cond,
        BBlock *ifTrue,
        BBlock *ifFalse) : Instruction(name, type, InstKind::Br, parent) {
          ops_.push_back(cond);
          ops_.push_back(ifTrue);
          ops_.push_back(ifFalse);
        }

GEP::GEP(const std::string &name,
          baseTypePtr type,
          BBlock *parent,
          Value *ptr,
          int offset) : Instruction(name, type, InstKind::GEP, parent) {
            ops_.push_back(ptr);
            ops_.push_back(new ConstIntValue(AddrLenPtr, offset));
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
                }