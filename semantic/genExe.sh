cd build/
./gimc_ir a.txt
llvm-link-19 start.ll ../../Test/lib/newlib.ll -o out.ll
