#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "../include/Config.h"
using namespace std;

// 用法：
// g++ -o 可执行程序名 check.cpp 
// ./可执行程序名 file1 file2
// 输出：
// check success 或者 check failed
#ifndef COMMIT_MODE
int main(int argc, char *argv[]) {
    argv++;
    if (argc > 0) {
        auto in1 = ifstream(argv[0]);
        auto in2 = ifstream(argv[1]);
        string s1, s2;
        while (!in1.eof()) {
            char c1;
            in1 >> c1;
            s1 = s1+c1;
        }
        while (!in2.eof()) {
            char c2;
            in2 >> c2;
            s2 = s2+c2;
        }
        if (s1 != s2) {
            cout << "check failed" << endl;
            return 1;
        }
        cout << "check success" << endl;
        return 0;
    }
    cout << "no input file" << endl;
    return 0;
}
#endif