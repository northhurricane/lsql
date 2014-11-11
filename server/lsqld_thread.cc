#include "lsqld_thread.h"

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
lthread_create(Thread *thread)
{
  int r = lthread_create(thread->func(), thread->para(), thread->thread());

  ThreadManager::GetInstance()->Add(thread);

  if (r == THREAD_SUCCESS)
    return LSQL_SUCCESS;

  return LSQL_ERROR;
}
