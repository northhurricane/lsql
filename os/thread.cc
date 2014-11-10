#include "thread.h"
#include <sched.h>

using namespace std;

void thread_sleep(uint32_t ms)
{
  int r;

  if (ms == 0)
  {
    r = sched_yield();
  }
  else
  {
    struct timespec requested_time;

    requested_time.tv_sec  = ms / 1000;
    requested_time.tv_nsec = (ms % 1000) * 1000000;
    r = nanosleep (&requested_time, NULL);
  }
  // if (r != 0)
  // {
  //   //出现错误
  // }
}

int thread_create(thread_function func, void *para, thread_t *thread)
{
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

  int r = pthread_create (thread, &attr, func, para);

  pthread_attr_destroy (&attr);

  if (r == 0)
    return THREAD_CREATE_SUCCEEDED;

  return THREAD_CREATE_FAILED;
}
