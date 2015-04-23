#include "vm.h"

/***************VFunction*****************/
#define SERIAL_UNDEFINE 0xFFFFFFFF
VFunction::VFunction()
{
  serial_ = SERIAL_UNDEFINE;
  first_ = NULL;
  second_ = NULL;
}


/***************VProcess*****************/
void
VProcess::Run()
{
  program_->Run(this);
}

void
VProcess::Initialize(VProgram *program)
{
  //生成process的bmemory_
  memory_ = AutoHeap::Create();

  //分配scene指针数组的空间
  uint32_t size = program->function_amount() * sizeof(VFScene*);
  scenes_ = (VFScene**)memory_->Allocate(size);

  //为每个函数进行scene的分配
  InitializeFunctionScene(program->entrance());
}

void
VProcess::Deinitialize()
{
  AutoHeap::Destroy(memory_);
}

bool
VProcess::InitializeFunctionScene(VFunction *function)
{
  //创建function自身的scene
  VFScene *pscene = function->CreateScene(this);
  VFScene **ppvfscene = scenes_ + function->serial();
  *ppvfscene = pscene;

  if (function->first() != NULL)
    InitializeFunctionScene(function->first());
  if (function->second() != NULL)
    InitializeFunctionScene(function->second());
}

/***************VProgram*****************/
VProgram::VProgram()
{
  entrance_ = NULL;
  function_amount_ = 0;
}

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
