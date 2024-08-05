#include "../include/LirToArm/LirToArm.h"
#include <list>

USING_GIMC_NAMESPACE

void LirToArm::genModule() {
  // 准备工作
  smartOut(".arch", "armv7", "right", "getMeyes");
}


void LirToArm::genFunction() {
  std::list<LirFunction*> funcs = lirModule_.getFunctions();
  for (auto func : funcs) {
    
  }
}

void LirToArm::genBlock() {

}