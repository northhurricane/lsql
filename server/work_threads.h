#ifndef _WORK_THREADS_H_
#define _WORK_THREADS_H_

#include "lsql.h"

class LPort;

lret work_threads_init();

lret work_threads_deinit();

void connect_task_enqueue(LPort *port);

//void disconnect_task_enque(LPort *port);

#endif //_WORK_THREADS_H_
