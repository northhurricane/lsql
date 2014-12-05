#include "task.h"
#include "lsqld_thread.h"
#include <iostream>

using namespace std;

static void* task_processing_thread(void *para);

task_t TaskManager::task_test_;
bool TaskManager::initialized_ = false;
Thread* TaskManager::threads_ = NULL;
lmutex_t TaskManager::mutex_;
lsemaphore_t TaskManager::semaphore_;
list<task_t*> TaskManager::queue_;

lret TaskManager::Initialize()
{
  initialized_ = true;

  lmutex_init(&mutex_);
  lsemaphore_init(&semaphore_, 0);

  StartProcessingThreads();

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

task_t *TaskManager::Allocate()
{
  return &task_test_;
}

void TaskManager::Free(task_t *task)
{
}

void TaskManager::Enqueue(task_t* task)
{
  lmutex_lock(&mutex_);
  queue_.push_back(task);
  lmutex_unlock(&mutex_);
  lsemaphore_post(&semaphore_);
}

task_t* TaskManager::Dequeue()
{
  lsemaphore_wait(&semaphore_);
  lmutex_lock(&mutex_);
  task_t *task = queue_.front();
  queue_.pop_front();
  lmutex_unlock(&mutex_);
  return task;
}

lret TaskManager::StartProcessingThreads()
{
  uint32_t thread_number = 1;

  Thread* threads = BuildThreadsInfo(thread_number);

  for (int i = 0; i < thread_number; i++)
    lret r = lsqld_thread_create(threads + i);

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
    task_t *task = TaskManager::Dequeue();
    cout << "task gotten";

    //判断是否是退出指令

    //执行任务
    task_process(task);
  }

  return NULL;
}

