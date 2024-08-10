#include "../../include/LIR/codegen/ToLir.h"
#include <set>
#include "../../include/Utils/BiMap.h"

USING_GIMC_NAMESPACE

ToLir::ToLir(Module irModule) : irModule(irModule){
  lirModule.setName(irModule.getName());
};

Function *armMemset;
Function *armMemcpy;

void ToLir::addArmFunc() {
  // void *memset(void *str, int c, size_t n)
  std::vector<baseTypePtr> arguTypes;
  arguTypes.push_back(int32PointerType);
  arguTypes.push_back(i32Type);
  arguTypes.push_back(i32Type);
  armMemset = new Function("memset", voidType, arguTypes);

  // void * memcpy ( void * destination, const void * source, size_t num );
  std::vector<baseTypePtr> arguTypes1;
  arguTypes1.push_back(int32PointerType);
  arguTypes1.push_back(int32PointerType);
  arguTypes1.push_back(i32Type);
  armMemcpy = new Function("memcpy", voidType, arguTypes1);

  bindGlobal(armMemcpy, new Addr(armMemcpy->getName()));  
  bindGlobal(armMemset, new Addr(armMemset->getName()));  
}

LirModule &ToLir::moduleGen() {
  // FPhyRegs 初始化
  FPhyReg::generateFPhyRegs();

  /**************************************************** 全局符号初始化 ************************************** */
  // 全局变量将 <label> 加入 map
  for (GlobalVar *globalVar : *irModule.getGlobalVars()) {
    lirModule.getGlobalvars()[globalVar->getName()] = globalVar;
    Addr *addr = new Addr(globalVar->getName());
    bindGlobal(globalVar, addr);
  }

  // 将 Function declares 的 <label> (名字) 加入 map，
  // 还需要一些参数的信息，如 iparamsInt, fparamsInt,
  for (Function *func : *irModule.getFuncDeclares()) {
    bindGlobal(func, new Addr(func->getName()));
    std::list<LirFunction*> & lirfuncs = lirModule.getFunctions();
    std::vector<baseTypePtr> &paramTypes = func->getArguTypes();

    // 新建 LIR Function
    LirFunction *lirFunc = new LirFunction(func->getName(), paramTypes.size());
    funcMap[func] = lirFunc;
    // 不能 push back 因为没有函数体，只能作为 Callee
    // lirModule.getFunctions().push_back(lirFunc);
    lirFunc->resolveParams(paramTypes);
  }

  // 将 Function defs 的 <label> 和 基本块的 <label> 放入 map
  for (Function *func : *irModule.getFuncDefs()) {

    // 绑定 Function <label>
    bindGlobal(func, new Addr(func->getName()));
    std::list<LirFunction*>& lirfuncs = lirModule.getFunctions();
    std::vector<baseTypePtr> paramTypes = func->getArguTypes();

    // 新建 LIR Function
    LirFunction *lirFunc = new LirFunction(func->getName(), paramTypes.size());
    funcMap[func] = lirFunc;
    lirModule.getFunctions().push_back(lirFunc);

    // 先为 BBLock 分配标签，生成 LirBlock 并加入 LirFunction 中
    if (func->getBBlockList().getSize() > 0) {
      INode<BBlock> *blockNode = func->getBBlockList().getHeadPtr();
      while (!blockNode->isEnd()) {
        blockNode = blockNode->getNext();
        BBlock *block = blockNode->getOwner();
        std::string lirBlkName = block->getName() + "_" + func->getName();
        LirBlock *lirBlock = new LirBlock(lirFunc, lirBlkName);

        // 将 LIR 基本块加入 LIRFunction
        lirFunc->appendBlk(lirBlock);
        // 构建 IR 基本块到 LIR 基本块映射
        blockMap[block] = lirBlock;
        // 为 LIR 基本块分配全局标签
        bindGlobal(block, new Addr(lirBlkName));
      }
    }
  }

  // 将仅仅在汇编中调用的，前端未声明，但 gcc 会自动链接的函数加入全局符号
  addArmFunc();

  /******************************************************  函数参数解析与 LIR Block 生成 ****************************************** */
  
  // 每个函数均维护一个双向的映射，获得其形参与物理寄存器的对应关系。
  std::map<Function*, BiMap<Value*, Reg*>> paramsInfos;

  for (Function *func : *(irModule.getFuncDefs())) {
    baseTypePtr funcType = func->getType();
    std::vector<baseTypePtr> paramTypes = func->getArguTypes();
    std::vector<Value> &funcParams = func->getArgus();
    int paramsCnt = paramTypes.size();
    std::vector<Value*> lirFuncParams;
    int intcnt = 0;
    int floatcnt = 0;

    LirFunction *lirFunc = funcMap[func];

    // idx 是为了后面方便物理寄存器找寻 function*，并构建 BiMap (后续建议全部重构，将 Value 和 reg 用一个双向的映射而非单向)
    std::set<int> idx = std::set<int>();

    // 双射 Map funcParam <-> PhyReg 
    BiMap<Value*, Reg*> biMap;

    /*********************** 处理 Function 参数 **********************/

    for (int i = 0; i < paramsCnt; i++) {
      if (!TypeBase::isFloat(funcParams[i].getType())) {
        intcnt++;
        idx.insert(i);
        lirFuncParams.push_back(&funcParams[i]);
 
        // 因为没有寄存器分配所以需要用虚拟寄存器装载 r0 ~ r3，在第一个基本块中处理
        bindValue(&funcParams[i], IPhyReg::getRegR(i));

        // 构建双射 map
        biMap.insert(&funcParams[i], IPhyReg::getRegR(i));
      }
      if (intcnt >= 4) {
        break;
      }
    }

    for (int i = 0; i < paramsCnt; i++) {
      if (TypeBase::isFloat(funcParams[i].getType())) {
        floatcnt++;
        idx.insert(i);
        lirFuncParams.push_back(&funcParams[i]);

        // 因为没有寄存器分配所以需要用虚拟寄存器装载 s0 ~ s15，在第一个基本块中处理
        bindValue(&funcParams[i], FPhyReg::getRegS(i));
        
        // 构建双射 map
        biMap.insert(&funcParams[i], FPhyReg::getRegS(i));
      }
      if (floatcnt >= 16) {
        break;
      }
    }

    for (int i = 0; i < paramsCnt; i++) {
      if (idx.count(i) == 0) {
        // 剩下的变量加入栈空间
        lirFunc->putParam(&funcParams[i]);
        lirFuncParams.push_back(&funcParams[i]);
      }
    }

    lirFunc->setLirFuncParams(lirFuncParams);
    lirFunc->setIParamsCnt(intcnt);
    lirFunc->setFParamsCnt(floatcnt);
    lirFunc->setReturnType(func->getType());

    // 将形参 BiMap 加入 paramsInfos 中
    paramsInfos.insert(std::pair<Function*, BiMap<Value*, Reg*>>(func, biMap));

    // 先为 BBLock 分配标签，生成 LirBlock 并加入 LirFunction 中
    // if (func->getBBlockList().getSize() > 0) {
    //   INode<BBlock> *blockNode = func->getBBlockList().getHeadPtr();
    //   while (!blockNode->isEnd()) {
    //     blockNode = blockNode->getNext();
    //     BBlock *block = blockNode->getOwner();
    //     std::string lirBlkName = block->getName() + "_" + func->getName();
    //     LirBlock *lirBlock = new LirBlock(lirFunc, lirBlkName);

    //     // 将 LIR 基本块加入 LIRFunction
    //     lirFunc->appendBlk(lirBlock);
    //     // 构建 IR 基本块到 LIR 基本块映射
    //     blockMap[block] = lirBlock;
    //     // 为 LIR 基本块分配全局标签
    //     bindGlobal(block, new Addr(lirBlkName));
    //   }
    // }
    // else {
    //   error("moduleGen: BBlock must have a size >= 1");
    // }

    /******************************* 为 LIR 基本块添加前驱后继 ******************************* */

    INode<BBlock> *blockNode = func->getBBlockList().getHeadPtr();
    // 由于 IR 中的 correctCheck 每个函数一定有 entry 块
    lirFunc->setEntry(blockMap[func->getEntryBBlock()]);
    while (!blockNode->isEnd()) {
      blockNode = blockNode->getNext();
      BBlock *block = blockNode->getOwner();
      LirBlock *lirBlock = blockMap[block];
      for (BBlock *preBlock : block->getPres()) {
        lirBlock->addPres(blockMap[preBlock]);
      }

      std::set<BBlock *> lirSuccs = block->getSuccs();
      if (lirSuccs.size() == 1) {
        lirBlock->setTrueLirSucc(blockMap[*lirSuccs.begin()]);
      } else if (lirSuccs.size() == 2) {
        lirBlock->setTrueLirSucc(blockMap[*lirSuccs.begin()]);
        lirBlock->setFalseLirSucc(blockMap[*lirSuccs.end()]);
      }
    }
  }

  /************************************************************* LIR 指令创建与解析 ************************************************************* */
  for (Function *func : *(irModule.getFuncDefs())) {

    // 函数信息初始化
    LirFunction *lirFunc = funcMap[func];
    setCheckingLirFunc(lirFunc);
    
    // 更新形参的 StackOffset，需要在 alloca 之前处理
    lirFunc->updateParamStack();
    
    // 首先遍历一遍所有基本块，将 alloca 指令全找出来
    // todo:为提高编译器速度，后续是否考虑 alloca 放在基本块开头？
    INode<BBlock> *blockNode = func->getBBlockList().getHeadPtr();
    while (!blockNode->isEnd()) {
      blockNode = blockNode->getNext();
      BBlock *bBLk = blockNode->getOwner();
      setCheckingLirBlock(blockMap[bBLk]);
      dealAlloca(bBLk);
    }
    
    /********************************* 第一个基本块特殊处理 ****************************** */
    
    // 因为需要 move 形参到虚拟寄存器
    blockNode = func->getBBlockList().getHeadPtr();
    blockNode = blockNode->getNext();
    BBlock *blk = blockNode->getOwner();
    setCheckingLirBlock(blockMap[blk]);

    // 根据每个函数的 BiMap 为形参添加 LirInstMove 指令 
    BiMap<Value*, Reg*> biMap = paramsInfos.at(func);

    // 查找进行传参的整数寄存器
    for (int i = 0; i < 4; i++) {
      IPhyReg *reg = IPhyReg::getRegR(i);
      if (biMap.containsValue(reg)) {
        IVReg *moveDst = new IVReg();
        LirInstMove *move = new LirInstMove(checkingBlock, moveDst, reg, LirArmStatus::NO_Cond);
        checkingBlock->addInst(move);
        bindValue(biMap.getKey(reg), moveDst);
      }
      else  break;  // 因为按照顺序传参，故可以 break;
    }

    // 查找进行传参的浮点寄存器
    for (int i = 0; i < 16; i++) {
      FPhyReg *reg = FPhyReg::getRegS(i);
      if (biMap.containsValue(reg)) {
        FVReg *moveDst = new FVReg();
        LirInstMove *move = new LirInstMove(checkingBlock, moveDst, reg, LirArmStatus::NO_Cond);
        checkingBlock->addInst(move);
        bindValue(biMap.getKey(reg), moveDst);
      }
      else  break;  // 因为按照顺序传参，故可以 break;
    }

    instResolve(blk);

    /********************************************* 后续基本块处理 ***************************************/ 

    while (!blockNode->isEnd()) {
      blockNode = blockNode->getNext();
      BBlock *bBlk = blockNode->getOwner();
      setCheckingLirBlock(blockMap[bBlk]);
      clearLocal();
      instResolve(bBlk);
    }
  }
#ifdef DEBUG_MODE
  for (auto func : lirModule.getFunctions()) {
    INode<LirBlock> *blkNode = func->getBlkList().getHeadPtr();
    while (!blkNode->isEnd()) {
      blkNode = blkNode->getNext();
      LirBlock *lirBlk = blkNode->getOwner();
      INode<LirInst> *instNode = lirBlk->getInst().getHeadPtr();
      while (!instNode->isEnd()) {
        instNode = instNode->getNext();
        LirInst *inst = instNode->getOwner();
        std::cout << LIRINST_STRING;
        std::fflush(stdout);
        LirOperand *opd1 = inst->getOpd1();
        LirOperand *opd2 = inst->getOpd2();
        LirOperand *opd3 = inst->getOpd3();
        if (opd1) {
          std::cout << opd1->toString() << ", ";
        }
        if (opd2) {
          std::cout << opd2->toString() << ", ";
        }
        if (opd3) {
          std::cout << opd3->toString() << ", ";
        }
        std::cout << std::endl;
      }
    }
  }
#endif
  return lirModule;
}

void ToLir::dealAlloca(BBlock *block) {
  LirFunction *lirFunc = funcMap[block->getParent()];
  LirBlock *lirBlock = blockMap[block];
  INode<Instruction> *instNode = block->getInstList().getHeadPtr();
  while (!instNode->isEnd()) {
    instNode = instNode->getNext();
    Instruction *inst = instNode->getOwner();

    // 或者，根据有没有在其他基本块出现，再来决定是否是需要在栈空间分配（一个指针变量的大小）
    if (inst->getKind() == InstKind::Alloca) {
      // 本身就是 ptr，放入 stackOffsetMap 中
      lirFunc->putLocalVar(inst);
    }

    bool isInSameBlock = true;

    BBlock *parentBlk = inst->getParent();    

    // 获取使用了自己的指令集合，若不同属于一个基本块，则为其分配一块栈内存
    for (auto use : inst->getUses()) {
      Instruction* useInst = dynamic_cast<Instruction*>(inst);
      if (useInst->getParent() != parentBlk) {
        isInSameBlock = false;
      }  
    }

    if (!isInSameBlock) {
      lirFunc->putCrossBlockVar(inst);
    }
  }
}

void ToLir::instResolve(BBlock *block) {

  LirFunction *lirFunc = funcMap[block->getParent()];
  LirBlock *lirBlock = blockMap[block];
  INode<Instruction> *instNode = block->getInstList().getHeadPtr();
  while (!instNode->isEnd()) {
    instNode = instNode->getNext();
    Instruction *inst = instNode->getOwner();
    InstKind kind = inst->getKind();

    // TODO:已经实现了整除加减乘除，需要实现其他二元指令
    if (kind > InstKind::BinaryOPBegin && kind < InstKind::BinaryOpEnd) {
      BinaryInst *i = dynamic_cast<BinaryInst *>(inst);
      Value *lhs = i->getLhs();
      Value *rhs = i->getRhs();
      LirOperand *lhsReg, *rhsReg, *dstReg;
      LirInstKind lirInstKind;
      switch (i->getKind()) {
        case InstKind::Add: {
          if (dynamic_cast<ConstValue *>(lhs)) {
            rhsReg = getBindOperand(lhs);
            lhsReg = getBindOperand(rhs);
          } else {
            lhsReg = getBindOperand(lhs);
            rhsReg = getBindOperand(rhs);
          }
          dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
          lirInstKind = LirInstKind::Add;
          break;
        }

        case InstKind::Sub: {
          if (dynamic_cast<ConstValue *>(lhs)) {
            rhsReg = getBindOperand(lhs);
            lhsReg = getBindOperand(rhs);
            lirInstKind = LirInstKind::Rsb; // 逆向减法
          } else {
            lhsReg = getBindOperand(lhs);
            rhsReg = getBindOperand(rhs);
            lirInstKind = LirInstKind::Sub;
          }
          dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
          break;
        }

        case InstKind::Mul: {
          if (dynamic_cast<ConstValue *>(lhs)) {
            rhsReg = getBindOperand(lhs);
            lhsReg = getBindOperand(rhs);
          } else {
            lhsReg = getBindOperand(lhs);
            rhsReg = getBindOperand(rhs);
          }
          dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
          lirInstKind = LirInstKind::Mul;
          break;
        }

        case InstKind::Div: {
          // 除法不可以交换
          lhsReg = getBindOperand(lhs);
          rhsReg = getBindOperand(rhs);
          dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
          lirInstKind = LirInstKind::Div;
          break;
        }

        case InstKind::Addf: {
          if (dynamic_cast<ConstValue *>(lhs)) {
            rhsReg = getBindOperand(lhs);
            lhsReg = getBindOperand(rhs);
          } else {
            lhsReg = getBindOperand(lhs);
            rhsReg = getBindOperand(rhs);
          }
          dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
          lirInstKind = LirInstKind::Addf;
          break;
        }

        case InstKind::Subf: {
          // if (dynamic_cast<ConstValue *>(lhs)) {
          //   rhsReg = getBindOperand(lhs);
          //   lhsReg = getBindOperand(rhs);
          //   // lirInstKind = LirInstKind::Rsbf;//逆向减法
          // } else {
            lhsReg = getBindOperand(lhs);
            rhsReg = getBindOperand(rhs);
            lirInstKind = LirInstKind::Subf;
          // }
          dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
          break;
        }

        case InstKind::Mulf: {
          if (dynamic_cast<ConstValue *>(lhs)) {
            rhsReg = getBindOperand(lhs);
            lhsReg = getBindOperand(rhs);
          } else {
            lhsReg = getBindOperand(lhs);
            rhsReg = getBindOperand(rhs);
          }
          dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
          lirInstKind = LirInstKind::Mulf;
          break;
        }

        case InstKind::Divf: {
          lhsReg = getBindOperand(lhs);
          rhsReg = getBindOperand(rhs);
          dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
          lirInstKind = LirInstKind::Divf;
          break;
        }

        // @todo 通过除法乘法减法来做
        case InstKind::SRem: {
          lhsReg = getBindOperand(lhs);
          rhsReg = getBindOperand(rhs);
          dstReg = ToLir::operandResolve(i, lirFunc, lirBlock);
          lirInstKind = LirInstKind::Div;
          // divident <- lhsReg / rhsReg
          LirBinary *divident = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
          lirBlock->addInst(divident);
          lirInstKind = LirInstKind::Mul;
          LirOperand *realLhs = lhsReg;
          lhsReg = dstReg;
          // 重新生成一个虚拟寄存器存储乘法 dstReg <- divident * rhsReg
          dstReg = operandResolve(i, lirFunc, lirBlock);
          LirBinary *multi = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
          // dstReg <- realLhs - divident * rhsReg
          lirInstKind = LirInstKind::Sub;
          lhsReg = realLhs;
          rhsReg = dstReg;
          dstReg = operandResolve(i, lirFunc, lirBlock);
          break;
        }
        default:
          break;
      }
      
      // 接下来将解析出的三个 reg 放入 <Value*, LirOperand*> map 中
      LirBinary *bin = new LirBinary(lirInstKind, lirBlock, lhsReg, rhsReg, dstReg);
      lirBlock->addInst(bin);
      bindValue(inst, dstReg);
    }

    // else if (kind == InstKind::Alloca) {
    //   // 本身就是 ptr，放入 stackOffsetMap 中
    //   lirFunc->putLocalVar(inst);
    // }

    else if (kind == InstKind::Store) {
      Store *i = dynamic_cast<Store *>(inst);
      Value *input = i->getInput();
      Value *ptr = i->getPtr(); // 注意这个 ptr 可能是形参，全局变量，局部变量
      LirOperand *data = getBindOperand(input); // 获取输入的 operand
      LirOperand *realAddr = getBindOperand(ptr);
      
      // 如果 realAddr 是全局变量地址，由于不能绝对寻址，故加一条 Mov，解析为 adr <reg>, <global>
      IVReg *addedReg = new IVReg();
      LirInstMove *move = new LirInstMove(lirBlock, addedReg, realAddr, LirArmStatus::NO_Cond);
      lirBlock->addInst(move);

      LirStore *lirStore = new LirStore(lirBlock, data, addedReg);
      lirBlock->addInst(lirStore);
    }

    else if (kind == InstKind::Load) {
      Load *i = dynamic_cast<Load *>(inst);
      Value *ptr = i->getPtr();
      LirOperand *dst =
          operandResolve(inst, lirFunc, lirBlock); // load 进的寄存器
      LirOperand *from = getBindOperand(ptr);
      LirLoad *lirLoad = new LirLoad(lirBlock, dst, from);
      lirBlock->addInst(lirLoad);
      bindValue(inst, dst);
    }

    else if (kind == InstKind::Call) {
      Call *i_ = dynamic_cast<Call *>(inst);
      Function *callee = i_->getFunc();
      LirFunction *lirCallee = funcMap[callee];
      std::vector<Value*> &params = i_->getArgus();
      int iparamsCnt = lirCallee->getIParamsCnt();
      int fparamsCnt = lirCallee->getFParamsCnt();
      int paramsCnt = iparamsCnt + fparamsCnt;
      int i;
      // i 从 1 开始迭代，因为第 0 个为 Function*
      for (i = 1; i <= iparamsCnt && i <= 4; i++) {
        // 这些参数是放在通用寄存器 r0 ~ r3 中的
        LirOperand *param = getBindOperand(params[i]);
        LirInstMove *move = new LirInstMove(lirBlock, IPhyReg::getRegR(i - 1), param, LirArmStatus::NO_Cond);
        lirBlock->addInst(move);
      }
      for (int j = 0; (i <= iparamsCnt + fparamsCnt) && (i <= iparamsCnt + 16); i++, j++) {
        // 这些参数是放在浮点寄存器 s0 ~ s15 中的
        LirOperand *param = getBindOperand(params[i]);
        LirInstMove *move = new LirInstMove(lirBlock, FPhyReg::getRegS(j), param, LirArmStatus::NO_Cond);
        lirBlock->addInst(move);
      }
      for (int j = paramsCnt; j >= i; j--) {
        // 这些参数存放在栈空间，逆序压栈
        LirOperand *param = getBindOperand(params[j]);
        LirPush *push = new LirPush(lirBlock, param);
        lirBlock->addInst(push);
      }
      // for (; i <= paramsCnt; i++) {
      //   // 这些参数存放在栈空间，逆序压栈
      //   LirOperand *param = getBindOperand(params[i]);
      //   // 从小到大将其一一对应到相应栈帧即可
      //   // // 注意这里应该是被调用函数的 stackOffsetMap
      //   // std::map<Value*, IImm>& map = lirCallee->getStackOffsetMap();
      //   // @C++_Learn 不理解为什么 map[params[i]].getImm() 不行
      //   int off = map.at(params[i]).getImm();
      //   LirOperand *offset = operandResolve(new ConstIntValue(off), lirFunc, lirBlock);
      //   IVReg *dst = new IVReg();
      //   // dst <- fp + offset
      //   LirBinary *bin = new LirBinary(LirInstKind::Add, lirBlock, IPhyReg::getRegR(FP_REG), offset, dst);
      //   // sdr param,[dst] 
      //   LirStore *store = new LirStore(lirBlock, param, dst);
      //   lirBlock->addInst(bin);
      //   lirBlock->addInst(store);
      // }
      LirCall *call = new LirCall(lirBlock, getBindOperand(callee));
      lirBlock->addInst(call);
      // 需要使用 InstMove 指令，将 r0 中返回值写入 dst 寄存器
      LirOperand *dst = operandResolve(inst, lirFunc, lirBlock);
      LirInstMove *move = new LirInstMove(lirBlock, dst, IPhyReg::getRegR(0), LirArmStatus::NO_Cond);
      lirBlock->addInst(move);
      bindValue(inst, dst);
    }

    else if (kind == InstKind::Ret) {
      Ret *i = dynamic_cast<Ret *>(inst);
      Value *ret = i->getRetValue();
      LirOperand *retVal = getBindOperand(ret);
      // 返回值放在 r0
      LirInstMove *move = new LirInstMove(lirBlock, IPhyReg::getRegR(0), retVal, LirArmStatus::NO_Cond);
      lirBlock->addInst(move);
      LirRet *lirRet = new LirRet(lirBlock);
      lirBlock->addInst(lirRet);
    }

    else if (kind == InstKind::Icmp) {
      Icmp *i = dynamic_cast<Icmp *>(inst);
      Value *first = i->getFirst();
      Value *second = i->getSecond();
      LirOperand *opd1 = getBindOperand(first);
      LirOperand *opd2 = getBindOperand(second);
      LirCmp *cmp = new LirCmp(lirBlock, opd1, opd2);
      lirBlock->addInst(cmp);
    }

    else if (kind == InstKind::Fcmp) {
      Fcmp *i = dynamic_cast<Fcmp *>(inst);
      Value *first = i->getFirst();
      Value *second = i->getSecond();
      LirOperand *opd1 = getBindOperand(first);
      LirOperand *opd2 = getBindOperand(second);
      // 注意在指令发射时需要将 fpu 中的状态寄存器赋值到 apsr 中，vmrs
      // APSR_nzcv, FPSCR
      LirCmp *cmp = new LirCmp(lirBlock, opd1, opd2);
      lirBlock->addInst(cmp);
    }

    else if (kind == InstKind::Br) {
      // 根据是否是无条件跳转
      Br *i = dynamic_cast<Br *>(inst);
      Value *bBlkTrue = i->getTrueBBlk();
      LirOperand *addr = getBindOperand(bBlkTrue);
      if (i->isUnconditional()) {
        LirBr *br = new LirBr(lirBlock, addr, LirArmStatus::NO_Cond);
        lirBlock->addInst(br);
      } else {
        // 加入两条 LirBr 指令
        Value *bBlkFalse = i->getFalseBBlk();
        Instruction *cond = dynamic_cast<Instruction *>(i->getCond());
        CondKind ckind = cond->getCondKind();
        LirOperand *falseAddr = getBindOperand(bBlkFalse);
        LirArmStatus status;
        SWCMP(cond->getKind(), ckind, &status);
        LirBr *br1 = new LirBr(lirBlock, addr, status);
        LirBr *br2 = new LirBr(lirBlock, falseAddr, LirArmStatus::NO_Cond);
        lirBlock->addInst(br1);
        lirBlock->addInst(br2);
      }
    }

    else if (kind == InstKind::GEP) {
      GEP *i = dynamic_cast<GEP *>(inst);
      Value *ptr = i->getPtr();
      Value *offset = i->getOffsetValue();
      LirOperand *addr = getBindOperand(ptr);
      LirOperand *shift = getBindOperand(offset);
      int baseSize = i->getType()->getSize();
      LirOperand *base = loadImmToIVReg(baseSize, lirFunc, lirBlock);
      // create 一条乘法指令，实现 baseSize * shift
      LirOperand *finalOffset = new IVReg();
      LirBinary *bin1 = new LirBinary(LirInstKind::Mul, lirBlock, shift, base, finalOffset);
      // create 一条加法指令，实现 finalOffset + addr
      LirOperand *dst = new IVReg();

      // 若为全局变量中的偏移 global_a_ptr + offset，则需要添加 instMove 指令
      if (addr->isAddr()) {
        IVReg *movReg1 = new IVReg();
        LirInstMove *movel = new LirInstMove(lirBlock, movReg1, addr, LirArmStatus::NO_Cond);
        lirBlock->addInst(movel);
        addr = movReg1;
      }

      LirBinary *bin2 = new LirBinary(LirInstKind::Add, lirBlock, addr, finalOffset, dst);
      bindValue(inst, dst);
      lirBlock->addInst(bin1);
      lirBlock->addInst(bin2);
    }

    else if (kind == InstKind::Fp2Int) {
      Fp2Int *i = dynamic_cast<Fp2Int *>(inst);
      Value *proto = i->getFp();
      LirOperand *dst = operandResolve(i, lirFunc, lirBlock);
      LirOperand *fp = getBindOperand(proto);
      LirFp2Int *fp2int = new LirFp2Int(lirBlock, dst, fp);
      lirBlock->addInst(fp2int);
      bindValue(inst, dst);
    }

    else if (kind == InstKind::Int2Fp) {
      Int2Fp *i = dynamic_cast<Int2Fp *>(inst);
      Value *proto = i->getInt();
      
      LirOperand *dst = operandResolve(i, lirFunc, lirBlock);
      LirOperand *integer = getBindOperand(proto);
      LirInt2Fp *int2fp = new LirInt2Fp(lirBlock, dst, integer);
      lirBlock->addInst(int2fp);
      bindValue(inst, dst);
    }

    else if (kind == InstKind::Zext) {
      Zext *i = dynamic_cast<Zext *>(inst);
      Instruction *proto = dynamic_cast<Instruction*>(i->getProto());
      
      // 虽然可以原地执行 Mov 指令（因为假设分配了 r0，执行 Mov 后 r0
      // 就是空闲的状态了）但是要满足无限虚拟寄存器的前提
      LirOperand *dst = operandResolve(proto, lirFunc, lirBlock);
      
      // 显然 proto 为一条 cmp 指令
      CondKind ckind = proto->getCondKind();
      LirArmStatus status;
      SWCMP(proto->getKind(), ckind, &status);
      
      // 赋值可能为 0 或 1
      LirOperand *opd0 = operandResolve(new ConstIntValue(0), lirFunc, lirBlock);
      LirOperand *opd1 = operandResolve(new ConstIntValue(1), lirFunc, lirBlock);
      
      // movw 不会修改状态寄存器，故可以插入两条 mov 一条为 movw，一条为 mov<Cond>
      // 这里移动的是立即数 (movw)0 或 (mov<Cond>)1，即满足 <Cond> 条件时才为 1
      // !!! 注意这里用到了条件执行，且两个 Move 指令可能使用了同一个 Vitual Reg，寄存器分配时应当注意这些信息。
      LirInstMove *move1 = new LirInstMove(lirBlock, dst, opd0, LirArmStatus::NO_Cond);
      LirInstMove *move2 = new LirInstMove(lirBlock, dst, opd1, status);
      lirBlock->addInst(move1);
      lirBlock->addInst(move2);
      bindValue(inst, dst);
    }

    else if (kind == InstKind::InitMem) {
      // 即调用 memset 即可，todo，数组非零初始化是否可以用 memcpy, 当然可以，动态链接库《程序员自我修养...》
      InitMem *i = dynamic_cast<InitMem *>(inst);
      Value *ptr = i->getPtr();
      LirOperand *length = operandResolve(new ConstIntValue(i->getLength()), lirFunc, lirBlock);
      LirOperand *pointer = getBindOperand(ptr);

      // 将第一个参数放入 r0 寄存器，第二个放入 r1，第三个放 r2
      LirInstMove *move = new LirInstMove(lirBlock, IPhyReg::getRegR(0), pointer, LirArmStatus::NO_Cond);
      LirInstMove *move2 = new LirInstMove(lirBlock, IPhyReg::getRegR(1), new IImm(0), LirArmStatus::NO_Cond);
      LirInstMove *move3 = new LirInstMove(lirBlock, IPhyReg::getRegR(2), length, LirArmStatus::NO_Cond);
      lirBlock->addInst(move);
      lirBlock->addInst(move2);
      lirBlock->addInst(move3);
      LirCall *call = new LirCall(lirBlock, getBindOperand(armMemset));
      lirBlock->addInst(call);
    }
  }
}

// OperandResolve 即为申请一个 Operand
LirOperand *ToLir::operandResolve(Value * val, LirFunction * lirFunc,
                                  LirBlock * lirBlock) {
  if (dynamic_cast<ConstValue *>(val)) {
    return immResolve(val, lirFunc, lirBlock);
  } else {
    //  这里 TypeBase 的检验需要用 isFloat，因为指针类型也在通用寄存器中
    if (TypeBase::isFloat(val->getType())) {
      return new FVReg();
    } else
      return new IVReg();
  }
}

LirOperand *ToLir::immResolve(Value * val, LirFunction * lirFunc,
                              LirBlock * lirBlock) {
  if (dynamic_cast<ConstFloatValue *>(val)) {
    return loadImmToFVReg(dynamic_cast<ConstFloatValue *>(val)->getFloat(),
                          lirFunc, lirBlock);
  } else {
    return loadImmToIVReg(dynamic_cast<ConstIntValue *>(val)->getInt(),
                          lirFunc, lirBlock);
  }
}

// 此处如果传递的是引用，那么局部变量会被销毁

// 将立即数移入 Float Reg
FVReg *ToLir::loadImmToFVReg(float val, LirFunction *lirFunc,
                              LirBlock *lirBlock) {
  FVReg *reg = new FVReg();
  FImm *fImm = new FImm(val);
  // todo 根据 val 的值，添加 mov 指令（1 条或 2 条）
  LirInstMove *move = new LirInstMove(lirBlock, reg, fImm, LirArmStatus::NO_Cond);
  lirBlock->addInst(move);
  lirFunc->getImmMap().emplace(reg, move);
  return reg;
}

// 将立即数移入 Integer Reg
IVReg *ToLir::loadImmToIVReg(int val, LirFunction *lirFunc,
                              LirBlock *lirBlock) {
  IVReg *reg = new IVReg();
  IImm *iImm = new IImm(val);
  // todo 根据 val 的值，添加 mov 指令（1 条或 2 条）
  LirInstMove *move = new LirInstMove(lirBlock, reg, iImm, LirArmStatus::NO_Cond);
  lirBlock->addInst(move);
  lirFunc->getImmMap().emplace(reg, move);
  return reg;
}

void ToLir::SWCMP(InstKind kind, CondKind ckind, LirArmStatus * status) {
  if (kind == InstKind::Fcmp) {
    switch (ckind.fCond) {
    case FCondKind::Oeq:
      *status = LirArmStatus::EQ;
      break;
    case FCondKind::Oge:
      *status = LirArmStatus::GE;
      break;
    case FCondKind::Ogt:
      *status = LirArmStatus::GT;
      break;
    case FCondKind::Ole:
      *status = LirArmStatus::LE;
      break;
    case FCondKind::Olt:
      *status = LirArmStatus::LT;
      break;
    case FCondKind::One:
      *status = LirArmStatus::NE;
      break;
    default:
      break;
    }
  } else {
    switch (ckind.iCond) {
    case ICondKind::Eq:
      *status = LirArmStatus::EQ;
      break;
    case ICondKind::Sge:
      *status = LirArmStatus::GE;
      break;
    case ICondKind::Sgt:
      *status = LirArmStatus::GT;
      break;
    case ICondKind::Sle:
      *status = LirArmStatus::LE;
      break;
    case ICondKind::Slt:
      *status = LirArmStatus::LT;
      break;
    case ICondKind::Ne:
      *status = LirArmStatus::NE;
      break;
    default:
      break;
    }
  }
}

LirOperand *ToLir::getBindOperand(Value *val) {
#ifdef DEBUG_MODE
  std::cout << "get BindOperand " << val->getFullName() << " from "  << checkingBlock->getLabel()  << " and " << checkingFunc->getFuncName() << std::endl; 
#endif
  // 可能为 IR 中的中间结果
  if (valMap.find(val) != valMap.end())
    return valMap[val];

  // 可能为 IR 中的 GlobalVar，Function，BBlock
  if (lirModule.getGlobalMap().find(val) != lirModule.getGlobalMap().end())
    return lirModule.getGlobalMap()[val];

  // 可能为 IR 中 ConstValue
  if (dynamic_cast<ConstValue*>(val)) {
    return immResolve(val, checkingFunc, checkingBlock);
  }
    
  // 可能为 IR 中的局部变量或形参，存在栈空间中，注意获取的为栈上位置，而非值本身
  std::map<Value*, IImm>& map = checkingFunc->getStackOffsetMap();
  if (map.find(val) != map.end()) {
    // 确实存在栈空间
    int offset = map.at(val).getImm();
    LirOperand *off = operandResolve(new ConstIntValue(offset), checkingFunc, checkingBlock);
    
    // 生成的 add 指令的目的虚拟寄存器
    LirOperand *addDst = operandResolve(val, checkingFunc, checkingBlock);
    LirBinary *realAddr = new LirBinary(LirInstKind::Add, checkingBlock, IPhyReg::getRegR(FP_REG), off, addDst);
    checkingBlock->addInst(realAddr);
// #ifdef DEBUG_MODE
//     std::cout << "从栈上获得 " << val->getFullName() << " with " << addDst->toString() << std::endl; 
// #endif
    // // 根据 OperandResolve 的要求，需要构建一个局部变量或形参基类的 Value*
    // std::shared_ptr<PointerType> ptrTy = std::make_shared<PointerType>(val->getType());
    // if (!ptrTy) {
    //   error("getBindOperand: 在栈空间中绑定了非指针类型的中端 Value");
    // }
    // Value *base = new Value("base", ptrTy->getBaseType());
    // // load 到一个虚拟寄存器中
    // LirOperand *loadDst = operandResolve(base, checkingFunc, checkingBlock);
    // LirLoad *getVar = new LirLoad(checkingBlock, loadDst, addDst);
// #ifdef DEBUG_MODE
//     std::cout << "load " << val->getFullName() << " to " << addDst->toString() << std::endl; 
// #endif
    // checkingBlock->addInst(getVar);
    // return loadDst;
    return addDst;
  }

  error("getBindOperand:" + val->getFullName() + "还未与 LirOperand 绑定");
  return nullptr;
}