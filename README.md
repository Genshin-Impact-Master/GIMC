# GIM Compiler

## 快速上手
### cmake 构建
```bash
cmake -Bbuild             # 创建 build 文件夹
cd build
make gimc_ir              # 构建 ir 样例 
cat tmp_outputIR.ll       # 查看输出的 LLVM 代码
clang++ tmp_outputIR.ll   # 生成可执行文件 a.out
./a.out
echo $?                   # 打印输出
```

