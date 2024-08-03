#include "../include/LirToArm/LirToArm1.h"

int main() {
  LirModule module = LirModule();
  LirToArm armCode(module);
  armCode.genModule();
}