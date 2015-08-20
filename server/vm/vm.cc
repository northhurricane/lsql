#include "vm.h"
#include "vmsql.h"
#include "lsqld_thread.h"

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


static int vm_running_thread(Thread *thread)
{
  void *para = thread->para();

  lsqld_thread_set_current(thread);

  while (true)
  {
    task_t *task = TaskManager::Dequeue();
    cout << "task gotten";

    //判断是否退出
    if (thread->stop_thread())
    {
      //线程退出
    }

    //执行任务
    task_process(task);
    TaskManager::Free(task);
  }

  return 0;
}

