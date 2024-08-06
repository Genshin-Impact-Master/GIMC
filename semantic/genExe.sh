cd build/
./gimc_ir a.txt
llvm-link-19 start.ll ../../Test/lib/newlib.ll -o out.ll
clang++ out.ll -fstack-usage
./a.out < ../../Test/functional/input/50_short_circuit.in > ../testout.out
echo $? >> ../testout.out