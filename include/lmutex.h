#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

struct lmutex_struct
{
  pthread_mutex_t mutex;
};
typedef struct lmutex_struct lmutex_t;

#define LMUTEX_SUCCESS  (0)
#define LMUTEX_ERROR    (-1)

int lmutex_init(lmutex_t *mutex);
int lmutex_destroy(lmutex_t *mutex);
int lmutex_lock(lmutex_t *mutex);
int lmutex_unlock(lmutex_t *mutex);

#endif //_MUTEX_H
