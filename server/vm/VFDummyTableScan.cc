#include "VFDummyTableScan.h"

void
VFDummyTableScan::Run(VProcess *process)
{
  VScene = process->GetScene(serial());
}

