#include "../../include/LIR/lirOperand/IImm.h"

USING_GIMC_NAMESPACE

std::string IImm::toString() {
            return std::to_string(imm);
} 

std::string IImm::toHexString() {
            std::ostringstream oss;
            oss << std::hex << imm;  // 将整数格式化为十六进制字符串  
            return oss.str();
}