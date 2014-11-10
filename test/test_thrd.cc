#include "thread.h"

#include <iostream>

using namespace std;

void *thrd_show_time(void *arg)
{
  int *pid = (int*)arg;
  int id = *pid;

  for (int i = 0; i < 10 ; i++)
  {
    cout << "thread " << id << ":" << i << " wake up" << endl;
    thread_sleep(100);
  }

  return 0;
}

int main()
{
  int ids[10];
  thread_t threads[10];

  for (int i = 0; i < sizeof(ids) / sizeof(int); i++)
  {
    ids[i] = i;
    thread_create(thrd_show_time, ids + i, threads + i);
    cout << "thread " << i << "created" << endl;
  }

  thread_sleep(10000);

  return 0;
}
