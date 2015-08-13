#include "lsqld_thread.h"

Thread::Thread()
{
}

Thread::Thread(lthread_function_t function, void *para, char *thread_info)
{
}


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

lret
lsqld_thread_create(Thread *thread)
{
  int r = lthread_create(thread->func(), thread->para(), thread->thread());

  ThreadManager::GetInstance()->Add(thread);

  if (r == THREAD_SUCCESS)
    return LSQL_SUCCESS;

  return LSQL_ERROR;
}

void
Thead::set_op_info(const char *op_info)
{
  //拷贝
  bool no_set_for_fast = true;
  if (no_set_for_fast)
    return ;

  strncpy(op_info_buffer_, op_info, OP_INFO_BUFFER_SIZE);
}
