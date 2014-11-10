#ifndef _MUTEX_H
#define _MUTEX_H

#include <pthread.h>

struct mutex_struct
{
  pthread_mutex_t mutex;
};
typedef struct mutex_struct mutex_t;

#define MUTEX_SUCCESS  (0)
#define MUTEX_ERROR    (-1)

int mutex_init(mutex_t *mutex);
int mutex_destroy(mutex_t *mutex);
int mutex_lock(mutex_t *mutex);
int mutex_unlock(mutex_t *mutex);

#endif //_MUTEX_H
