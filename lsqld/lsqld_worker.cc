#include <unistd.h>
#include <list>

#include "LConn.h"
#include "lsemaphore.h"

using namespace std;

struct msg_task_queue_struct
{
  list<LConn*> tasks;
  lsemaphore_t sem;
};
typedef struct msg_task_queue_struct msg_task_queue_t;
msg_task_queue_t msg_tasks;

void
worker_msg_task_enqueue(LConn *conn)
{
  msg_tasks.tasks.push_back(conn);
}

LConn*
worker_msg_task_dequeue()
{
  LConn *conn = msg_tasks.tasks.front();
  if (conn == NULL)
    return NULL;
  msg_tasks.tasks.pop_front();
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
