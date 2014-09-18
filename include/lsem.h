#ifndef _LSEM_H
#define _LSEM_H

#include "lsql.h"
#include <semaphore.h>

typedef void *lsem_t;

lret lsem_init(lsem_t *sem, unsigned int value);
lret lsem_destroy(lsem_t sem);
lret lsem_wait(lsem_t sem);
lret lsem_post(lsem_t sem);

#endif //_LSEM_H
