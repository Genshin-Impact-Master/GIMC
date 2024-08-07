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
        /**
         * @note 寄存器分配后得到的映射 
         * LirOperand -> int
         * int 表示为寄存器的编号，而 int 编号又对应于相应寄存器
         * @see Config.h
         */
        std::map<LirOperand*, int> regAllocMap;
    protected:
        // 三元式最多三个操作寄存器
        LirOperand *opd1;
        LirOperand *opd2;
        LirOperand *opd3;
        LirArmStatus status;

    public:
        LirInst(LirInstKind kind, LirBlock *parent_);
        LirInstKind getKind() {return lirKind;}
        LirBlock* getParent() {return parent;}
        INode<LirInst> &getNode() {return lirInstNode;}
        void setParent(LirBlock* parent) {this->parent = parent;}
        void setKind(LirInstKind kind) {this->lirKind = kind;}

        LirOperand* getOpd1() {return opd1;}
        LirOperand* getOpd2() {return opd2;}
        LirOperand* getOpd3() {return opd3;}

        /**
         * 为无限寄存器分配实际寄存器
         * @param opd 选择分配的寄存器
         * @param armRegNum arm 寄存器的编号，其中通用寄存器为 0 ~ 15，浮点寄存器为 16 ~ ? todo
         */
        void allocaReg(LirOperand *opd, int armRegNum) {regAllocMap[opd] = armRegNum;}

        // LIR 到 arm 汇编 codegen 时调用
        std::string getOperandName(LirOperand *opd) {
          if (opd->isVirtual()) {
            // 若为分配的寄存器  
            return ARM_REGS[regAllocMap[opd]];
          }
          // 注意：到这一步时必须保证超过 arm 指令限定长度的立即数需要转换为 Addr? 是否是这样处理？todo
          else if (opd->isImm() || opd->isAddr()) {
            return opd->toString();
          }
          else {
            error("暂时不支持其他种类的寄存器"); 
          }
          return "null";
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
   * @param ptr 需要加载的寄存器位置
   */
  LirLoad(LirBlock *parent, LirOperand *dst, LirOperand *ptr);
};

class LirRet : public LirInst {
public:
  /**
   * @param retVal 存有返回值的寄存器
   */
  LirRet(LirBlock *parent, LirOperand *retVal);
};

class LirBr : public LirInst {
public:
  /**
   * @param addr 跳转的标签地址
   * @param status_ ARM 状态码即跳转条件判断种类
   */
  LirBr(LirBlock *parent, LirOperand *addr, LirArmStatus status_);
};

class LirCmp : public LirInst {
public:
  /**
   * @param opd1 reg1
   * @param opd2 reg2
   */
  LirCmp(LirBlock *parent, LirOperand *opd1, LirOperand *opd2);
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
GIMC_NAMESPACE_END


#endif