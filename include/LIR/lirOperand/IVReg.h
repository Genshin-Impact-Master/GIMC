#ifndef LIR_IVREG_H
#define LIR_IVREG_H
#include "../../Config.h"
#include "lirOperand.h"
#include "Reg.h"

GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE

class IVReg : public Reg {
    private:
        static int count;
        int id;
    
    public:
        IVReg() : Reg(LirOperandKind::IVirtual), id() {
          id = count++; 
          if (id > 2000) {
            exit(1);
          }
        };

        IVReg(int id) : Reg(LirOperandKind::IVirtual), id(id){};

        std::string toString() override;
};

GIMC_NAMESPACE_END

#endif