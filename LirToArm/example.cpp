#include "../include/LirToArm/LirToArm1.h"

int main() {
  LirModule module();
  LirToArm armCode(module);
  armCode.genModule();
}