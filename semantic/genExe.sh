cd build/
make
./gimc_ir a.txt 
llvm-link-19 start ../../Test/lib/newlib.ll -o out.ll
clang++ out.ll -fstack-usage
./a.out < ../../Test/hidden_functional/input/09_BFS.in > ../testout.out
echo $? >> ../testout.out