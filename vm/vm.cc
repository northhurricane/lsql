#include "vm.h"
#include "vmsql.h"
#include "lsqld_thread.h"


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
    //判断是否退出
    if (thread->stop_thread())
    {
      //线程退出
    }

    //执行任务
  }

  return 0;
}

