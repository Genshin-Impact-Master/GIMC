#!/bin/bash

SCC="arm-linux-gnueabihf-gcc"
QEMU="qemu-arm"
ARM_FLAGS="-cpu cortex-a7"
COMPILE_FLAGS="-march=armv7 -mfpu=vfpv3 -mfloat-abi=hard -fPIC"
LLVM_LINK="llvm-link"
QEMU_FLAGS="-L /usr/arm-linux-gnueabihf"

# 函数用法说明
usage() {
    echo "Usage: $0 -dir DIR [-single NUM | -all] [-emit-llvm | -S]"
    exit 1
}

# 参数处理
while [[ "$#" -gt 0 ]]; do
    case $1 in
        -dir) DIR="$2"; shift ;;
        -single) SINGLE="$2"; ISTMP=true; shift ;;
        -all) ALL=true ;;
        -emit-llvm) EMIT_LLVM=true ;;
        -S) S=true ;;
        *) usage ;;
    esac
    shift
done

# 检查DIR参数是否存在
if [ -z "$DIR" ]; then
    usage
fi

# 设置INTEGRATE为脚本所在目录
INTEGRATE=$(realpath $(dirname "$0"))

# 进入指定目录
cd "$DIR" || { echo "Directory $DIR does not exist."; exit 1; }
mkdir -p "$INTEGRATE/tmpDir"

CLANGEXE="$INTEGRATE/tmpDir/ClangExe"
GIMCASM="$INTEGRATE/tmpDir/GimcASM"
GIMCEXE="$INTEGRATE/tmpDir/GimcExe"
LLDir="$INTEGRATE/tmpDir/LLDir"
GIMC="$INTEGRATE/build/compiler"

# 创建tmpDir一系列目录
mkdir -p $LLDir
mkdir -p $CLANGEXE
mkdir -p $GIMCASM
mkdir -p $GIMCEXE

# 选择文件
if [ "$ALL" = true ]; then
    FILES=syFile/*.sy
elif [ -n "$SINGLE" ]; then
    FILES=syFile/${SINGLE}*.sy
else
    usage
fi

# set -x

# 设置最大栈空间为 4g
ulimit -s 4096000

# 遍历文件并运行测试
for syfile in $FILES; do
    base=$(basename "$syfile" .sy)
    infile="input/${base}.in"
    clangoutfile="$CLANGEXE/${base}.out"
    tmpDir="$INTEGRATE/tmpDir"
    stdOut="stdOut/${base}.out"

    if [ "$EMIT_LLVM" = true ]; then
        if [ "$ISTMP" = true ]; then
            outllfile="$INTEGRATE/tmp_${base}.ll"
            tmpOUT="$INTEGRATE/tmp_${base}_clang.out"
        else
            outllfile="$LLDir/${base}.ll"
            tmpOUT="$CLANGEXE/${base}.out"
        fi
        $GIMC "$syfile" -emit-llvm -o $outllfile
        echo "export $outllfile"
        $LLVM_LINK $outllfile ../lib/newlib.ll -S -o "$tmpDir/tmp_.ll"
        clang "$tmpDir/tmp_.ll" -fstack-usage -o "$tmpDir/tmp"
        if [ -f "$infile" ]; then
            "$tmpDir/tmp" < "$infile" > "$tmpOUT"
            echo $? >> "$tmpOUT"
        else
            "$tmpDir/tmp" > "$tmpOUT"
            echo $? >> "$tmpOUT"
        fi
    elif [ "$S" = true ]; then
        if [ "$ISTMP" = true ]; then
            tmpGIMC_S="$INTEGRATE/tmp_${base}.s"
            tmpOUT="$GIMCASM/tmp_${base}_gimc.out"
        else
            tmpGIMC_S="$GIMCASM/${base}.s"
            tmpOUT="$GIMCEXE/${base}.out"
        fi
        $GIMC -S -o "$tmpGIMC_S" "$syfile"
        $SCC $COMPILE_FLAGS "$tmpGIMC_S" ../lib/newlib.o -o "$tmpDir/tmp"
        # if [ -f "$infile" ]; then
        #     $QEMU $ARM_FLAGS $QEMU_FLAGS "$tmpDir/tmp" < "$infile" > "$tmpOUT"
        #     echo $? >> "$tmpOUT"
        #     echo "${base}"
        #     "$INTEGRATE/check" "$tmpOUT" $stdOut || exit
        # else
        #     $QEMU $ARM_FLAGS $QEMU_FLAGS "$tmpDir/tmp" > "$tmpOUT"
        #     echo $? >> "$tmpOUT"
        #     echo "${base}"
        #     "$INTEGRATE/check" "$tmpOUT" $stdOut || exit
        # fi
    else
        usage
    fi
done
