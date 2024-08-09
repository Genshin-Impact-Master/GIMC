#ifndef LIR_INST_H
#define LIR_INST_H
#include "../../Config.h"
#include "../lirOperand/lirOperand.h"
#include "../lirOperand/IImm.h"
#include "../lirOperand/Imm.h"
#include "../lirOperand/FImm.h"
#include "../lirOperand/Addr.h"
#include "../../Utils/IList.h"
#include <map>

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE
class LirBlock;
enum class LirInstKind {
    BinaryBegin,
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
    BinaryEnd,
    Store,
    Load,
    Call,
    Ret,
    cmp,
    Br,
    Fp2Int,
    Int2Fp,
    Move,      // Move 指令，转移寄存器的值
    Push,
    Pop
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
        // 三元式最多三个操作寄存器
        std::vector<LirOperand*> opds;
        LirArmStatus status;
    public:
        LirInst(LirInstKind kind, LirBlock *parent_);
        LirInstKind getKind() {return lirKind;}
        LirBlock* getParent() {return parent;}
        INode<LirInst> &getNode() {return lirInstNode;}
        void setParent(LirBlock* parent) {this->parent = parent;}
        void setKind(LirInstKind kind) {this->lirKind = kind;}

        // opd1 只能存放 destination，适用于 binary，load，Fp2Int，Int2Fp，move 
        LirOperand* getOpd1() {return opds[0];}
        LirOperand* getOpd2() {return opds[1];}
        LirOperand* getOpd3() {return opds[2];}

        // 设置寄存器
        void setOpd1(LirOperand *opd) {opds[0] = opd;}
        void setOpd2(LirOperand *opd) {opds[0] = opd;}
        void setOpd3(LirOperand *opd) {opds[0] = opd;}

        std::vector<LirOperand*> &getOpds() {return opds;}

        bool isBinary() {return lirKind > LirInstKind::BinaryBegin && lirKind < LirInstKind::BinaryEnd;}

        // 是否为 Fp2Int 或 Int2Fp
        bool isIFChange() {return lirKind == LirInstKind::Fp2Int || lirKind == LirInstKind::Int2Fp;}

        // LIR 到 arm 汇编 codegen 时调用
        std::string getOperandName(LirOperand *opd) {
          if (opd->isVirtual()) {
            // 若为分配的寄存器  
            error("getOperandName: 还存在虚拟寄存器，请保证进行寄存器分配且正确");
          }
          // 注意：到这一步时必须保证超过 arm 指令限定长度的立即数需要转换为 Addr? 是否是这样处理？todo
          return opd->toString();
        }

        // 加入 inst 指令前
        void addBefore(LirInst *inst) {
          INode<LirInst> &node = inst->getNode();
          lirInstNode.addBefore(&node);
        }

        // 获取下一条指令
        LirInst* getNextInst() {
          return lirInstNode.getNext()->getOwner();
        }
};

class LirStore : public LirInst {
public:
  /**
   * @param addr 存取的位置
   * @param input 需要存入的 Operand
   */
  LirStore(LirBlock *parent, LirOperand *addr, LirOperand *input);
};

class LirLoad : public LirInst {
public:
  /**
   * @param dst 加载的寄存器
   * @param ptr 需要加载的寄存器在栈中的位置
   */
  LirLoad(LirBlock *parent, LirOperand *dst, LirOperand *ptr);
};

class LirRet : public LirInst {
public:
  LirRet(LirBlock *parent);
};

class LirBr : public LirInst {
public:
  /**
   * @param addr 跳转的标签地址，在 opd2
   * @param status_ ARM 状态码即跳转条件判断种类
   */
  LirBr(LirBlock *parent, LirOperand *addr, LirArmStatus status_);
};

class LirCmp : public LirInst {
public:
  /**
   * @param opd2 reg1
   * @param opd3 reg2
   */
  LirCmp(LirBlock *parent, LirOperand *opd2, LirOperand *opd3);
};

class LirFp2Int : public LirInst {
public:
  /**
   * @param proto 需要改变的 Value
   */
  LirFp2Int(LirBlock *parent, LirOperand *dst, LirOperand *proto);
};

class LirInt2Fp : public LirInst {
public:
  LirInt2Fp(LirBlock *parent, LirOperand *dst, LirOperand *proto);
};

class LirCall : public LirInst{
public:
  /**
   * @param func 被调用的函数，显然一定为一个 Addr （全局符号，汇编为： bl <label>），存在 opd2
   */
  LirCall(LirBlock *parent, LirOperand *func);
};

class LirPush : public LirInst {
public:
  LirPush(LirBlock *parent, LirOperand *reg);
};

class LirPop : public LirInst {
public:
  LirPop(LirBlock *parent, LirOperand *reg);
};
GIMC_NAMESPACE_END


#endif