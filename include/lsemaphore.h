#ifndef LSQL_INCLUDE_LSEMAPHORE_H_
#define LSQL_INCLUDE_LSEMAPHORE_H_

#include <semaphore.h>
#include <stdint.h>

struct lsemaphore_struct
{
  sem_t sem;
};
typedef struct lsemaphore_struct lsemaphore_t;

#define LSEMAPHORE_SUCCESS (0)
#define LSEMAPHORE_ERROR   (-1)

int lsemaphore_init(lsemaphore_t *sem, uint32_t value);
int lsemaphore_wait(lsemaphore_t *sem);
int lsemaphore_post(lsemaphore_t *sem);
int lsemaphore_destroy(lsemaphore_t *sem);

#endif //LSQL_INCLUDE_LSEMAPHORE_H_
