#ifndef LIR_ADDR_H
#define LIR_ADDR_H
#include "../../Config.h"
#include "lirOperand.h"
GIMC_NAMESPACE_BEGIN
USING_GIMC_NAMESPACE


class Addr : public LirOperand {
    private:
        std::string label;
    
    public:
        Addr(std::string label);

        std::string toString();

};

GIMC_NAMESPACE_END
#endif