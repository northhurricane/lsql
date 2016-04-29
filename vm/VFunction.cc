#include "VFunction.h"

VFunction::VFunction()
{
  serial_ = VF_SERIAL_UNDEFINE;
}


vfreturn_t
VFunction::Execute(VProcess *process)
{
  vfreturn_t ret;
  ret = ActionBeforeLeftFunctionCall();

  ret = left_->Execute(process);

  ret = ActionAfterLeftFunctionCall();

  ret = right_->Execute(process);

  ret = ActionAfterRightFunctionCall();
}

