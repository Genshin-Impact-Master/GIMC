#include "../include/IR/IRBuilder.h"
#include "genIR.hpp"

// 每个 example 必须包含
Function *myFunc;                               // main 函数
BBlock *entry;                                  // main 中首个基本块 entry
std::vector<Function*> *defs;                          // 函数定义容器
std::vector<Function*> *declares;                      // 函数声明容器
std::vector<GlobalVar*> *globals;                      // 全局变量容器


NumberPtr parseExp(ExpPtr exp){
    switch (exp -> getType()){
    case ExpType::ET_INT:{
        auto tmp = dynamic_pointer_cast<Number>((dynamic_pointer_cast<UnaryExp>(exp)) -> getExp());
        return tmp;
    }
    default:
        return nullptr;
    }
}

void genIR(char* filename, string dump) {
    CompUnit* root = parse(filename);
    IRBuilder builder = IRBuilder(dump, nullptr, nullptr);
    Module* module = new Module("start", voidType);
    vector<DeclPtr> global_decls = root->getDecl();
    for (DeclPtr decl : global_decls) {
        if (decl -> isConst()) {
            auto tmp = decl -> getConstDecl();
            auto type = int32PointerType;
            for (auto def: tmp -> getConstDef()->getConstDef()){
                // Instruction* inst = builder.createAllocaInst(def -> getIdentifier(), type);
                // builder.createStoreInst(new ConstIntValue(parseExp(def-> getInitVal() ->getExp())->getIntVal()), inst);
                GlobalVar* var = builder.createGlobalVar<Value*>(def -> getIdentifier(), 
                                                                 type, 
                                                                 new ConstIntValue(parseExp(def-> getInitVal() ->getExp())->getIntVal()));
                globals -> push_back(var);
            }
        }
        else {
            auto tmp = decl -> getVarDecl();
            auto type = int32PointerType;
            for (auto def: tmp -> getVarDefs()->getVarDef()){
                GlobalVar* var = nullptr;
                if (def -> isInit()) {
                    var = builder.createGlobalVar<Value*>(def -> getIdentifier(), 
                                                                 type, 
                                                                 new ConstIntValue(parseExp(def-> getInitVal())->getIntVal()));
                }
                else {
                    var = builder.createGlobalVar<Value*>(def -> getIdentifier(), 
                                                                 type, 
                                                                 new ConstIntValue(0));
                }
                globals -> push_back(var);
            }
        }
    }

    builder.emitIRModule(module);
}

int main(int argc, char *argv[]){
    ++ argv;
    if (argc > 0) genIR(argv[0], "testout.ll");
    else {
        printf("No input file\n");
        return 0;
    }
    return 0;
}