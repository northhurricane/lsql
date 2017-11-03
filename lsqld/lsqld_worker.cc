#include <unistd.h>
#include <list>

#include "LConn.h"
#include "lsemaphore.h"
#include "lmutex.h"

using namespace std;

struct msg_task_queue_struct
{
  list<LConn*> tasks;
  lsemaphore_t sem;
  lmutex_t mutex;
};
typedef struct msg_task_queue_struct msg_task_queue_t;
msg_task_queue_t msg_tasks;

void
worker_msg_task_enqueue(LConn *conn)
{
  lmutex_lock(&msg_tasks.mutex);
  msg_tasks.tasks.push_back(conn);
  lmutex_unlock(&msg_tasks.mutex);

  lsemaphore_post(&msg_tasks.sem);
}

LConn*
worker_msg_task_dequeue()
{
  lsemaphore_wait(&msg_tasks.sem);
  lmutex_lock(&msg_tasks.mutex);
  LConn *conn = msg_tasks.tasks.front();
  if (conn != NULL)
    msg_tasks.tasks.pop_front();
  lmutex_unlock(&msg_tasks.mutex);
  return conn;
}

void
msg_woker_thrd()
{
  LConn *conn = NULL;
  while (true)
  {
    /*    msg_task_dequeue();
          msg_proc(conn);*/
  }
}

void
vm_worker_thrd()
{
  while (true)
  {
    //vm_task_dequeue();
  }
}
