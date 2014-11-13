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
