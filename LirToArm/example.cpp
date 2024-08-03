#include "../include/LirToArm/LirToArm.h"
#include <map>
USING_GIMC_NAMESPACE

int main() {
  LirModule module = LirModule();
  // LirToArm armCode(module);
  // armCode.genModule();
  std::map<std::string, GlobalVar*> gs = module.getGlobalvars();
  std::vector<Value*> shit_a;
  shit_a.push_back(new ConstIntValue(123));
  shit_a.push_back(new ConstIntValue(13));
  shit_a.push_back(new ConstIntValue(3));
  
  std::vector<Value*> shit_b;
  shit_b.push_back(new ConstFloatValue(12.5));
  shit_b.push_back(new ConstFloatValue(1.3));
  shit_b.push_back(new ConstFloatValue(3.0));
  baseTypePtr ty1 = std::make_shared<PointerType>(i32Type, 2);
  baseTypePtr ty2 = std::make_shared<PointerType>(floatType, 3);
  GlobalVar a = GlobalVar("a", ty1, shit_a);
  GlobalVar b = GlobalVar("b", ty2, shit_b);
  gs.insert(std::pair<std::string, GlobalVar *>("a", &a));
  gs.insert(std::pair<std::string, GlobalVar *>("b", &b));
  LirToArm armCode = LirToArm(module);
  armCode.Output_Arm_global();
}