#include "vm.h"

void
VProcess::Run()
{
  program_->Run(this);
}


void
VProgram::Run(VProcess *process)
{
  _entrance->Run(process);
}

