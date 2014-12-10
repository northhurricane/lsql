#include "task.h"
#include "conn.h"
#include "sess.h"
#include "lmessage_login.h"
#include "lmessage_prepare.h"
#include "sql_process.h"

static void
task_authenticate(lmessage_login_request_t *request)
{
}

static void
task_process_login(Connection *connection, Message *message)
{
  lmessage_login_request_t login_request;
  lmessage_login_request_read(message, &login_request);
  task_authenticate(&login_request);
  Session *session = SessionManager::CreateSession(connection);
}

static void
task_process_execution(Session *session, Message *message)
{
}

static void
task_process_prepare(Session *session, Message *message)
{
  lmessage_prepare_request_t request;
  lmessage_prepare_request_read(message, &request);
  sql_process_prepare(NULL, request.sql_text, request.length);
}

void
task_process_message(Connection *conn)
{
  Message *message = conn->message();
  uint16_t logicId = message->ReadLogicId();
  switch (logicId)
  {
  case LMSG_LOGIC_ID_LOGIN:
    return task_process_login(conn, message);

  case LMSG_LOGIC_ID_EXECUTION:
    return task_process_execution(conn->session(), message);

  case LMSG_LOGIC_ID_PREPARE:
    return task_process_prepare(conn->session(), message);
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
    }

}
