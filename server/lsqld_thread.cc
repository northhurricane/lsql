#include "lsqld_thread.h"

LThread::LThread()
{
}

/*LThread::LThread(lthread_function_t function, void *para, char *thread_info)
{
}*/


LThreadManager* LThreadManager::instance_ = (LThreadManager*)NULL;

LThreadManager::LThreadManager()
{
  lmutex_init(&mutex_);
}

lret LThreadManager::Initialize()
{
  instance_ = new LThreadManager();

  return LSQL_SUCCESS;
}

lret LThreadManager::Deinitialize()
{
  delete instance_;

  return LSQL_SUCCESS;
}

/*void
Thead::set_op_info(const char *op_info)
{
  //拷贝信息
  bool no_set_for_fast = true;
  if (no_set_for_fast)
    return ;

  //Todo : 上锁。
  strncpy(op_info_buffer_, op_info, OP_INFO_BUFFER_SIZE);
  }*/

////////////////////////
lret
lsqld_thread_init()
{
  return LSQL_SUCCESS;
}

lret
lsqld_thread_deinit()
{
  return LSQL_SUCCESS;
}

static __LTLS__ LThread *curr_thread = NULL;

lret
lsqld_thread_create(LThread *thread)
{
  lthread_function_t thrd_func = (lthread_function_t)thread->func();

  lthread_t thread_id;
  //int r = lthread_create(thread->func(), thread->para(), &thread_id);
  int r = 0;
  if (r == THREAD_ERROR)
    return LSQL_ERROR;

  thread->set_thread(thread_id);

  LThreadManager::GetInstance()->Add(thread);

  return LSQL_SUCCESS;
}

LThread*
lsqld_thread_current()
{
  return curr_thread;
}

void
lsqld_thread_set_current(LThread *thread)
{
  curr_thread = thread;
}
