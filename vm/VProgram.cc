#include "VProgram.h"
#include "VProcess.h"

VProgram::VProgram()
{
  function_amount_ = 0;
}

bool VProgram::Bind(VSQL *vsql)
{
}

void VProgram::Run(VProcess *process)
{
}

bool
VProgram::GenerateFunctionSerial(VFunction *function)
{
  function->set_serial(function_amount_);
  function_amount_++;

  if (function->first() != NULL)
    GenerateFunctionSerial(function->first());

  if (function->second() != NULL)
    GenerateFunctionSerial(function->second());

  return true;
}

bool
VProgram::Link(VFunction *entrance)
{
  entrance_ = entrance;

  GenerateFunctionSerial(entrance);

  return true;
}

