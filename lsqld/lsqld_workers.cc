#include "LConn.h"


void
msg_woker_thrd()
{
  LConn *conn = NULL;
  while (true)
  {
    msg_task_dequeue();
    msg_proc(conn);
  }
}

void
vm_worker_thrd()
{
  while (true)
  {
    vm_task_dequeue();
  }
}
