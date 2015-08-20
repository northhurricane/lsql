#include "vm.h"
#include "vmsql.h"

void
VProgram::Run(VProcess *process)
{
  entrance_->Run(process);
}

bool
VProgram::Link(VFunction *entrance)
{
  entrance_ = entrance;

  GenerateFunctionSerial(entrance);

  return true;
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
VProgram::BindSql(VMSQL *sql)
{
  vmsql_ = sql;
  vmsql_->Link();

  return true;
}
