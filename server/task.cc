#include "task.h"
#include "lmessage.h"
#include <iostream>

using namespace std;

static void task_process_connection(TASK *task)
{
  //alloc session object
}

static lret task_send_execute_result(SESSION *session)
{
  CONNECTION *connection = session->connection;
  enet_socket_send(connection->socket, "done", 4, 0);
}

static lret task_process_execute(SESSION *session, MESSAGE *message)
{
  r = enet_socket_recv(message->socket, message->buffer,
                       sizeof(message->buffer_fast), 0);
  {
    message->buffer_fast[r] = LEND;
    cout << message->buffer_fast << endl;
  }

  //do the real things here

  task_send_execution_message(session);

  return LSQL_SUCCESS;
}

static lret task_process_message(SESSION *session, lmessage_t *message)
{
  uint16_t command = lmessage_read_command(message->head);

  switch (command)
  {
    case LCMD_EXECUTE:
      return task_process_execute(session, message);
      break;
  }

  return LSQL_SUCCESS;
}

static void task_process_request(TASK *task)
{
  CONNECTION connection = task->connection;
  MESSAGE *message = MESSAGE::allocate();

  lret r = message->begin(connection);

  if (connection->message.totol_length == 0)
  {
    //client connection was close. cancel and clear all related 
    //with this connection
  }

  //process message
  r = task_process_message(connection->session, message);
  r = message.end();
  MESSAGE::free(message);
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
