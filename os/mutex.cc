#include "lsql.h"
#include "mutex.h"

int mutex_init(mutex_t *mutex)
{
  pthread_mutex_init(&mutex->mutex, NULL);

  return MUTEX_SUCCESS;
}

int mutex_destroy(mutex_t *mutex)
{
  pthread_mutex_destroy(&mutex->mutex);
  return MUTEX_SUCCESS;
}

int mutex_lock(mutex_t *mutex)
{
  pthread_mutex_lock(&mutex->mutex);
  return MUTEX_SUCCESS;
}

int mutex_unlock(mutex_t *mutex)
{
  pthread_mutex_unlock(mutex->mutex);
  return MUTEX_SUCCESS;
}

