#include "VFunction.h"

VFunction::VFunction()
{
  serial_ = VF_SERIAL_UNDEFINE;
  first_ = NULL;
  second_ = NULL;
}


void
VFunction::Execute(VProcess *process)
{
  //执行左侧
  process->CallFunc(first_);
  ActionAfterFirstFunc(process);

  VFScene *scene = process->GetScene(serial());

  if (seconde() != NULL)
  {
    if (scene->over())
    {
      //assert: second函数必须是初始化（initialized）或者重置（reset）状态
    }
    else
    {
      //进行第二函数的执行
      process->CallFunc(second_);
      ActionAfterSecondFunc();
    }
  }
}

