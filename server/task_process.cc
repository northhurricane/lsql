#include "task.h"
#include "conn.h"
#include "sess.h"
#include "lmessage_login.h"
#include "lmessage_prepare.h"
#include "lmessage_execute.h"
#include "sql_process.h"
#include "llog.h"

static void
task_process_login(Connection *connection, Message *message)
{
  lmsg_login_req_t login_request;
  //lmsg_login_request_read(message, &login_request);
  Session *session = SessionManager::CreateSession(connection);
}

static void
task_process_execution(Session *session, Message *message)
{
  //llog_trace("task_process_execution", "task_process_execution 1");
  lmsg_execute_req_t request;
  //lmsg_execute_req_read(message, &request);

  //todo : 判断是否存在参数，读取传入的参数

  if (request.exec_direct)
  {
    //to do : 从消息中读取SQL语句，将SQL语句生成计划
    char * sql = NULL;
    uint32_t sql_len = 0;
    //sql_process_build(NULL, sql, sql_len);
  }

  //to do : 执行命令
  sql_process_execute(NULL);
}

static void
task_process_prepare(Session *session, Message *message)
{
  lmsg_prepare_req_t request;
  lmsg_prepare_req_read(message, &request);
  //sql_process_prepare(NULL, request.sql_text, request.length);
}

void
task_process_message(Connection *conn)
{
  Message *message = conn->message();
  /*uint16_t logicId = message->ReadLogicId();
  switch (logicId)
  {
  case LMSG_LOGIC_ID_LOGIN:
    return task_process_login(conn, message);

  case LMSG_LOGIC_ID_EXECUTION:
    return task_process_execution(conn->session(), message);

  case LMSG_LOGIC_ID_PREPARE:
    return task_process_prepare(conn->session(), message);
  }
  */
}

/*void
task_process_pi(Task *task)
{
  Connection *conn = (Connection*)(task->content);
  conn->Reciver();
  if (!conn->Valid())
  {
    return ;
  }
  task_process_message(conn);
}
*/

/*
void
task_process_rr(Task *task)
{
}
*/

void
task_process(const task_t *task)
{
  //process message
  switch (task->type)
  {
  case TASK_PI:
    break;
  case TASK_RR:
    break;
  default:
    //assert(false);
    break;
  }

  /*  if (task->type == TASK_PROCESS_MESSAGE)
  {
    //recive request message
    Connection *conn = (Connection*)(task->content);
    conn->Recieve();
    if (!conn->Valid())
    {
      //连接无效，关闭连接
      return ;
    }
    }*/
}
