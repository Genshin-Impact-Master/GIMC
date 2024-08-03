#include "../../Config.h"

#ifndef LIR_OPERAND_H
#define LIR_OPERAND_H

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

enum class LirOperandKind {
        IVirtual,
        IPhy,
        FVirtual,
        FPhy,
        IImm,
        FImm,
        Addr
};

class LirOperand {
    private:
        LirOperandKind OperandKind ;

    public:
        LirOperand() {}

        LirOperand(LirOperandKind kind);
        
        bool isImm();
        
        bool isInt();
        
        bool isFloat();

        bool isVirtual();
        
        bool isPhy();
        
        LirOperandKind getKind();

        std::string print();




    
};



GIMC_NAMESPACE_END

#endif