#include "VProgram.h"
#include "VProcess.h"

VProgram::VProgram()
{
  entrance_ = NULL;
  function_amount_ = 0;
}

VProgram::Run(VProcess *process)
{
  process->CallFunc(entrance_);
}

