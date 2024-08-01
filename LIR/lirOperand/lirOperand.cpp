#include "../../include/LIR/lirOperand/lirOperand.h"

USING_GIMC_NAMESPACE

LirOperand::LirOperand(LirOperandKind kind) : OperandKind(kind) {};

bool LirOperand::isImm() {return (OperandKind == LirOperandKind::IImm) || (OperandKind == LirOperandKind::FImm);}

bool LirOperand::isInt() {
            return (OperandKind == LirOperandKind::IVirtual) 
            || (OperandKind == LirOperandKind::IPhy)
            || (OperandKind == LirOperandKind::IImm);
}

bool LirOperand::isFloat() {
            return (OperandKind == LirOperandKind::FVirtual) 
            || (OperandKind == LirOperandKind::FPhy)
            || (OperandKind == LirOperandKind::FImm);
}

bool LirOperand::isVirtual() {return (OperandKind == LirOperandKind::IVirtual) || (OperandKind == LirOperandKind::FVirtual);}

bool LirOperand::isPhy() {return (OperandKind == LirOperandKind::IPhy) || (OperandKind == LirOperandKind::FPhy);}

LirOperandKind LirOperand::getKind() {return OperandKind;}

std::string LirOperand::print() {return toString();}


