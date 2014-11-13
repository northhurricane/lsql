#include "lthread.h"
#include "lsemaphore.h"

#include <iostream>

using namespace std;

lsemaphore_t sem;

void *thrd_show_time(void *arg)
{
  int *pid = (int*)arg;
  int id = *pid;

  {
    cout << "thread " << id << ":" << " start up" << endl;
    lthread_sleep(100);
    cout << "wait for semaphore" << endl;
    lsemaphore_wait(&sem);
  }

  return 0;
}

int main()
{
  int ids[10];
  lthread_t threads[10];

  lsemaphore_init(&sem, 0);
  for (int i = 0; i < sizeof(ids) / sizeof(int); i++)
  {
    ids[i] = i;
    lthread_create(thrd_show_time, ids + i, threads + i);
    cout << "thread " << i << "created" << endl;
  }

  lthread_sleep(10000);

  for (int i = 0; i < sizeof(ids) / sizeof(ids[0]); i++)
  {
    lsemaphore_post(&sem);
  }

  lthread_sleep(10000);
  lsemaphore_destroy(&sem);

  return 0;
}
