# GIM Compiler

## 快速上手
### cmake 构建
```bash
cmake -Bbuild                                       # 创建 build 文件夹
cd build
make gimc_ir                                        # 构建 ir 样例 
./gimc_ir                                           # 执行输出 llvm 文件
cat tmp_outputIR.ll                                 # 查看输出的 LLVM 代码
llvm-link tmp_outputIR.ll ../IR/lib.ll -S -o out.ll # 生成链接后的 llvm 文件
clang++ out.ll                                      # 生成可执行文件 a.out
./a.out
echo $?                                             # 打印输出
```

