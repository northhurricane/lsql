#include "vm.h"

/***************VProcess*****************/
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

/***************VProgram*****************/

void
VProgram::Run(VProcess *process)
{
  entrance_->Run(process);
}

