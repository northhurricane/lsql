#include "task.h"
#include "conn.h"

/*

*/
static void
task_process_login()
{
}

static void
task_process_execution()
{
}

static void
task_process_prepare()
{
}

void
task_process_message(Connection *conn)
{
  Message *message = conn->message();
  uint16_t logicId = message->ReadLogicId();
  switch (logicId)
  {
  case LMSG_LOGIC_ID_LOGIN:
    return task_process_login();

  case LMSG_LOGIC_ID_EXECUTION:
    return task_process_execution();

  case LMSG_LOGIC_ID_PREPARE:
    return task_process_prepare();
  }
}

void
task_process(const task_t *task)
{
    //process message
    if (task->type == TASK_PROCESS_MESSAGE)
    {
      //recive request message
      Connection *conn = (Connection*)(task->content);
      conn->Recieve();
      if (!conn->Valid())
      {
        //连接无效，关闭连接
        return ;
      }
      //process message

      //send result message
      conn->Send();
    }

}
