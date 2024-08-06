#include "../../include/LIR/lirInst/LirInst.h"

USING_GIMC_NAMESPACE

LirInst::LirInst(LirInstKind kind, LirBlock *parent_) : 
                lirInstNode(nullptr, nullptr, this),
                parent(parent_),
                lirKind(kind) {}
