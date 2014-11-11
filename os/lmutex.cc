#include "lsql.h"
#include "lmutex.h"

int lmutex_init(lmutex_t *mutex)
{
  pthread_mutex_init(&mutex->mutex, NULL);

  return LMUTEX_SUCCESS;
}

int lmutex_destroy(lmutex_t *mutex)
{
  pthread_mutex_destroy(&mutex->mutex);
  return LMUTEX_SUCCESS;
}

int lmutex_lock(lmutex_t *mutex)
{
  pthread_mutex_lock(&mutex->mutex);
  return LMUTEX_SUCCESS;
}

int lmutex_unlock(lmutex_t *mutex)
{
  pthread_mutex_unlock(&mutex->mutex);
  return LMUTEX_SUCCESS;
}

