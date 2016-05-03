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
  //判断是否退出
  if (ret.error == true)
  {
    //错误退出
  }
  if (ret.over == true)
  {
    //执行结束退出
  }

  if (left_)
  {
    ret = left_->Execute(process);
    //判断是否成功
    if (ret.error == true)
    {
      //错误退出
    }
  }

  ret = ActionAfterLeftFunctionCall(ret);
  //判断是否退出
  if (ret.error == true)
  {
  }

  if (right_)
  {
    ret = right_->Execute(process);
    //判断是否成功
    if (ret.error)
    {
    }

    ret = ActionAfterRightFunctionCall(ret);
  }

  return ret;
}

