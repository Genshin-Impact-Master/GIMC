#include "../semantic/genIR.hpp"
std::vector<Function*> *defs;                          // 函数定义容器
std::vector<Function*> *declares;                      // 函数声明容器
std::vector<GlobalVar*> *globals;                      // 全局变量容器
SymbolTable sym_tb = SymbolTable();
string error_msg = "";
IRBuilder builder;
Module* module;
int main(int argc, char* argv[]){
    ++ argv;
    if (argc > 0) {
        // 运行格式必须是 ./compiler input -S -o output!!!!
        char *filename = argv[0];
        char *dumpfilename = argv[3];
        // 生成IRModule 
        genIRModule(argv[0]);
        builder.emitIRModule(module, dumpfilename);
        builder.close();
        return 0;
    }
    else {
        printf("No input file\n");
        return 0;
    }
}