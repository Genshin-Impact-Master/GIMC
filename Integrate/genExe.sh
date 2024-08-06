cd build/
make
./compiler a.txt -S -o a.out
llvm-link-19 a.out.ll ../../Test/lib/newlib.ll -o a.out.ll
clang++ a.out.ll -fstack-usage
./a.out < ../../Test/hidden_functional/input/09_BFS.in > ../testout.out
echo $? >> ../testout.out