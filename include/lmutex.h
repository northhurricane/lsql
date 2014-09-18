#ifndef _LMUTEX_H
#define _LMUTEX_H

#include <pthread.h>
#include "lsql.h"

typedef void *lmutex_t;

lret lmutex_init(lmutex_t *mutex);
lret lmutex_destroy(lmutex_t mutex);
lret lmutex_lock(lmutex_t mutex);
lret lmutex_unlock(lmutex_t mutex);

#endif //_LMUTEX_H
