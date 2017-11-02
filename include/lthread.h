#ifndef LSQL_INCLUDE_LTHREAD_H_
#define LSQL_INCLUDE_LTHREAD_H_

#include <pthread.h>
#include <stdint.h>

//#ifdef __LSQL_LINUX
#define __LTLS__ __thread
//#else
//#endif

//typedef int (*lthread_function_t) (void *);
typedef void *(*lthread_function_t) (void *);
typedef pthread_t lthread_t;

#define THREAD_SUCCESS (0)
#define THREAD_ERROR (-1)

int lthread_create(lthread_function_t func, void *para, lthread_t *thread);
void lthread_sleep(uint32_t ms);

#endif //LSQL_INCLUDE_LTHREAD_H_

