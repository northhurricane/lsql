#include "lthread.h"
#include <sched.h>

using namespace std;

void lthread_sleep(uint32_t ms)
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

int lthread_create(lthread_function_t func, void *para, lthread_t *thread)
{
  pthread_attr_t attr;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

  int r = 0;
  //int r = pthread_create (thread, &attr, func, para);

  pthread_attr_destroy (&attr);

  if (r == 0)
    return THREAD_SUCCESS;

  return THREAD_ERROR;
}
