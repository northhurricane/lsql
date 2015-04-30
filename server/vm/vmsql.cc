#include "vmsql.h"

VMSQL::VMSQL()
{
  entrance_ = NULL;
  function_amount_ = 0;
}

void
VMSQL::Run(VProcess *process)
{
  entrance_->Run(process);
}

bool
VMSQL::Link()
{
  lassert(entrance_ != NULL);

  GenerateFunctionSerial(entrance_);

  return true;
}

bool
VMSQL::GenerateFunctionSerial(VFunction *function)
{
  function->set_serial(function_amount_);
  function_amount_++;

  if (function->first() != NULL)
    GenerateFunctionSerial(function->first());

  if (function->second() != NULL)
    GenerateFunctionSerial(function->second());

  return true;
}

