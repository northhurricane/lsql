#include "lsqld_thread.h"

Thread::Thread()
{
}

/*Thread::Thread(lthread_function_t function, void *para, char *thread_info)
{
}*/


ThreadManager* ThreadManager::instance_ = (ThreadManager*)NULL;

ThreadManager::ThreadManager()
{
  lmutex_init(&mutex_);
}

lret ThreadManager::Initialize()
{
  instance_ = new ThreadManager();

  return LSQL_SUCCESS;
}

lret ThreadManager::Deinitialize()
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
static __LTLS__ Thread *curr_thread = NULL;

lret
lsqld_thread_create(Thread *thread)
{
  lthread_function_t thrd_func = (lthread_function_t)thread->func();

  lthread_t thread_id;
  //int r = lthread_create(thread->func(), thread->para(), &thread_id);
  int r = 0;
  if (r == THREAD_ERROR)
    return LSQL_ERROR;

  thread->set_thread(thread_id);

  ThreadManager::GetInstance()->Add(thread);

  return LSQL_SUCCESS;
}

Thread*
lsqld_thread_current()
{
  return curr_thread;
}

void
lsqld_thread_set_current(Thread *thread)
{
  curr_thread = thread;
}
