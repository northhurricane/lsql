#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>
#include <stdint.h>

typedef void *(*thread_function) (void *);
typedef pthread_t thread_t;

#define THREAD_SUCCESS (0)
#define THREAD_ERROR (-1)

int thread_create(thread_function func, void *para, thread_t *thread);
void thread_sleep(uint32_t ms);

#endif //_THREAD_H

