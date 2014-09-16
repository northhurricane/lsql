#ifndef _LTHRD_H
#define _LTHRD_H

#include "lsql.h"
#include <pthread.h>
#include <unistd.h>

/*
//for register in program
struct lthrd_head_struct
{
  int threadid;
};
typedef struct lthrd_head_struct lthrd_head_t;

struct lthrd_struct
{
  lthrd_head_t head;
  void *ptr;        //function thread specific info
};
typedef struct lthrd_struct lthrd_t;*/

typedef  void *(*start_routine_t) (void *);

inline lret lthrd_create(start_routine_t routine, void *arg)
{
  pthread_attr_t attr;
  pthread_t thread;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
  pthread_create (&thread, &attr, routine, arg);
  pthread_attr_destroy (&attr);
}

inline void lthrd_sleep(unsigned int seconds)
{
  sleep(seconds);
}

#endif // _LTHRD_H
