#include "lsemaphore.h"

int lsemaphore_init(lsemaphore_t *sem, uint32_t value)
{
  sem_init(&sem->sem, 0, (unsigned int)value);
  return LSEMAPHORE_SUCCESS;
}
int lsemaphore_wait(lsemaphore_t *sem)
{
  sem_wait(&sem->sem);
  return LSEMAPHORE_SUCCESS;
}

int lsemaphore_post(lsemaphore_t *sem)
{
  sem_post(&sem->sem);
  return LSEMAPHORE_SUCCESS;
}

int lsemaphore_destroy(lsemaphore_t *sem)
{
  sem_destroy(&sem->sem);
  return LSEMAPHORE_SUCCESS;
}
