#include "task.h"

static void task_process_connection(TASK *task)
{
  //alloc session object
}

static void task_process_request(TASK *task)
{
}

static void task_process_response(TASK *task)
{
}

void task_execute(TASK *task)
{
  switch (task->type)
  {
  case TASK_CONNECTION:
    task_process_connection(task);
    break;
  case TASK_REQUEST:
    task_process_request(task);
    break;
  case  TASK_RESPONSE:
    task_process_response(task);
    break;
  }
  
}

TASK *TASK::alloc()
{
  return NULL;
}

void TASK::free(TASK *task)
{
}

TASK *TASK::dequeue()
{
  return NULL;
}

void TASK::enqueue(TASK *task)
{
}
