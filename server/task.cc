#include "task.h"
#include "lmessage.h"
#include "lsqld_thread.h"

using namespace std;

static void* task_processing_thread(void *para);

bool TaskManager::initialized_ = false;
Thread* TaskManager::threads_ = NULL;
lmutex_t TaskManager::mutex_;
lsemaphore_t TaskManager::semaphore_;

lret TaskManager::Initialize()
{
  initialized_ = true;

  lmutex_init(&mutex_);
  lsemaphore_init(&semaphore_, 0);

  return LSQL_SUCCESS;
}

lret TaskManager::Deinitialize()
{
  initialized_ = false;

  if (threads_ != NULL)
    delete threads_;

  lmutex_destroy(&mutex_);
  lsemaphore_destroy(&semaphore_);

  return LSQL_SUCCESS;
}

Task* TaskManager::Dequeue()
{
  return NULL;
}

lret TaskManager::StartProcessingThreads()
{
  uint32_t thread_number = 6;

  Thread* threads = BuildThreadsInfo(thread_number);

  for (int i = 0; i < thread_number; i++)
    lsqld_thread_create(threads + i);

  return LSQL_SUCCESS;
}

Thread* TaskManager::BuildThreadsInfo(uint32_t number)
{
  Thread *threads = new Thread[number];
  for (int i = 0; i < number; i++)
  {
    threads[i].set_func(task_processing_thread);
    threads[i].set_para(threads + i);
  }

  return threads;
}

static void* task_processing_thread(void *para)
{
  Thread *thread = (Thread*)para;

  while (true)
  {
    Task *task = TaskManager::Dequeue();
  }

  return NULL;
}

