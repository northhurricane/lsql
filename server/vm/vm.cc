#include "vm.h"

void
VProcess::Run()
{
  program_->Run(this);
}

void
VProcess::Initialize(VProgram *program)
{
}

void
VProcess::Deinitialize()
{
}

VFScene *
VProcess::GetScene(uint32_t serial)
{
  return NULL;
}


void
VProgram::Run(VProcess *process)
{
  entrance_->Run(process);
}

