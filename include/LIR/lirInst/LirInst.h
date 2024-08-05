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

class LirInst {
    private:
        LirInstKind lirKind;
        LirBlock* parent;
        INode<LirInst> lirInstNode;

    public:
        LirInstKind getKind() {return lirKind;}
        LirBlock* getParent() {return parent;}
        INode<LirInst> &getNode() {return lirInstNode;}
        void setParent(LirBlock* parent) {this->parent = parent;}
        void setKind(LirInstKind kind) {this->lirKind = kind;}

};



GIMC_NAMESPACE_END


#endif