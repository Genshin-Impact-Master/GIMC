#ifndef LIR_INST_H
#define LIR_INST_H
#include "../../Config.h"
#include "../lirOperand/lirOperand.h"

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE
class LirBlock;
enum class LirInstKind {
    Add,
    Sub,
    Rsb, //这个是逆向指令
    Mul,
    Div,
    SRem,
    Addf,
    Subf,
    Mulf,
    Divf,
    Store,
    Load,
    Call,
    Ret,
    cmp,
    Br,
    Fp2Int,
    Int2Fp,
    Move      // Move 指令，转移寄存器的值
};

enum class LirArmStatus {
  EQ,
  NE,
  GT,
  LT,
  GE,
  LE,
  NO_Cond   // 无条件跳转，b <label>
};

class LirInst {
    private:
        LirInstKind lirKind;
        LirBlock* parent;
        INode<LirInst> lirInstNode;
    protected:
        std::vector<LirOperand*> lirOpds;
        LirArmStatus status;

    public:
        LirInst(LirInstKind kind, LirBlock *parent_) {}
        LirInstKind getKind() {return lirKind;}
        LirBlock* getParent() {return parent;}
        INode<LirInst> &getNode() {return lirInstNode;}
        void setParent(LirBlock* parent) {this->parent = parent;}
        void setKind(LirInstKind kind) {this->lirKind = kind;}

};

class LirStore : public LirInst {
public:
  LirStore(LirBlock *parent, LirOperand *offset, LirOperand *input) : LirInst(LirInstKind::Store, parent) {
    lirOpds.push_back(offset); 
    lirOpds.push_back(input);
  }
};

class LirLoad : public LirInst {
public:
  LirLoad(LirBlock *parent, LirOperand *dst, LirOperand *ptr) : LirInst(LirInstKind::Load, parent) {
    lirOpds.push_back(dst);
    lirOpds.push_back(ptr);
  }
};

class LirRet : public LirInst {
public:
  LirRet(LirBlock *parent, LirOperand *retVal) : LirInst(LirInstKind::Ret,  parent) {
    lirOpds.push_back(retVal);
  }
};

class LirBr : public LirInst {
public:
  LirBr(LirBlock *parent, LirOperand *addr, LirArmStatus status_) : LirInst(LirInstKind::Br, parent) {
    lirOpds.push_back(addr);
    status = status_;
  }
};

class LirCmp : public LirInst {
public:
  LirCmp(LirBlock *parent, LirOperand *opd1, LirOperand *opd2) : LirInst(LirInstKind::cmp, parent) {
    lirOpds.push_back(opd1);
    lirOpds.push_back(opd2);
  }
}

GIMC_NAMESPACE_END


#endif