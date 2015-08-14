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
list<task_t*> TaskManager::pi_queue_;
list<task_t*> TaskManager::rr_queue_;

lret TaskManager::Initialize()
{
  initialized_ = true;

  lmutex_init(&pi_mutex_);
  lmutex_init(&rr_mutex_);
  lmutex_init(&free_mutex_);
  lsemaphore_init(&semaphore_, 0);

  StartProcessingThreads();

  return LSQL_SUCCESS;
}

lret TaskManager::Deinitialize()
{
  initialized_ = false;

  if (threads_ != NULL)
    delete threads_;

  lmutex_destroy(&pi_mutex_);
  lmutex_destroy(&rr_mutex_);
  lmutex_destroy(&free_mutex_);
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

void TaskManager::EnqueuePI(task_t* task)
{
  lmutex_lock(&pi_mutex_);
  pi_queue_.push_back(task);
  lmutex_unlock(&pi_mutex_);
  lsemaphore_post(&semaphore_);
}

task_t* TaskManager::DequeuePI()
{
  task_t *task = NULL;
  lmutex_lock(&pi_mutex_);
  if (!pi_queue_.empty())
  {
    task = pi_queue_.front();
    pi_queue_.pop_front();
  }
  lmutex_unlock(&pi_mutex_);
  return task;
}

void TaskManager::EnqueueRR(task_t* task)
{
  lmutex_lock(&rr_mutex_);
  rr_queue_.push_back(task);
  lmutex_unlock(&rr_mutex_);
  lsemaphore_post(&semaphore_);
}

task_t* TaskManager::DequeueRR()
{
  task_t *task = NULL;
  lmutex_lock(&rr_mutex_);
  if (!rr_queue_.empty())
  {
    task = rr_queue_.front();
    rr_queue_.pop_front();
  }
  lmutex_unlock(&rr_mutex_);
  return task;
}

task_t *TaskManager::Dequeue()
{
  task_t *task = NULL;
  lsemaphore_wait(&semaphore_);
  //查看rr queue是否有任务
  if (!rr_queue_.empty())
    task = DequeueRR();
  //在争用的情况下，可能出现有一个task thread获得rr task，但另外一个没获取到，所以需要检查
  if (task != NULL)
    return task;
  task = DequeuePI();

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
    Free(task);
  }

  return NULL;
}

