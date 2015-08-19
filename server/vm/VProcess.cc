#include "VProcess.h"

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

