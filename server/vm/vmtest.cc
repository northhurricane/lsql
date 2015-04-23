#include "vm.h"
#include "VFCalc.h"
#include "VFDummyTableScan.h"

void testSelectConst()
{
  //构造program部分
  VProgram program;
  VFCalc calc;
  VFDummyTableScan dummyTable;
  calc.set_first(&dummyTable);
  bool success = program.Link(&calc);

  //虚拟进程运行
  VProcess process;
  process.Initialize(&program);
  process.Run();
  process.Deinitialize();
}


int main(int argc, char* argv[])
{
  testSelectConst();

  return 0;
}
