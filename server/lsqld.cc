#include "lsqld.h"
#include "task.h"
#include "enet.h"
#include "conn.h"
#include "lthrd.h"

static void lsqld_start_task_worker_thrds();
static void lsqld_init_net();
static void lsqld_deal_net_event();

//the purpose to place main function at first is that I wish beginner
//can locate main branch as quick as possible. 
//Also abstracting what the server do to functions help beginner
//understanding this program better
int lsqld_main(int argc, char *argv[])
{
  LSQLD::initialize(argc, argv);

  lsqld_start_task_worker_thrds();

  lsqld_init_net();

  lsqld_deal_net_event();

  return 0;
}

//reading run-time variable from cmd-line and option file
lret LSQLD::initialize(int argc, char *argv[])
{
  instance = new LSQLD();
  //set default
  instance->port = 5966;

  return LSQL_SUCCESS;
}

LSQLD *LSQLD::instance = NULL;

static void lsqld_init_net()
{
  LSQLD *lsqld = LSQLD::get_instance(); 
  short port = lsqld->port;

  int r;

  enet_socket_t socket = NULL;
  r = enet_socket_create(&socket, port);
  if (r == -1)
  {
    lerror("failed to create socket");
    lexit(1);
  }

  enet_t enet = NULL;
  r = enet_create(&enet, 10);
  if (r == -1)
  {
    lerror("failed to create enet");
    goto error;
  }

  struct enet_event event;
  event.data.ptr = socket;
  r = enet_add_socket(enet, socket, &event);
  if (r == -1)
  {
    lerror("failed to add sockedt");
    goto error;
  }

  lsqld->enet = enet;
  lsqld->socket = socket;

  return ;
error:
  if (socket != NULL)
    enet_socket_destroy(socket);
  if (enet != NULL)
    enet_destroy(enet);

  lexit(1);
}

static void lsqld_deal_connection(enet_socket_t socket);
static void lsqld_deal_request(void *socket_data);

static void lsqld_deal_net_event()
{
#define MAXEVENTS 10
  struct enet_event events[MAXEVENTS];
  LSQLD *lsqld = LSQLD::get_instance();
  enet_t enet = lsqld->enet;
  enet_socket_t socket = lsqld->socket;

  int r;
  while (true)
  {
    r = enet_wait(enet, events, MAXEVENTS, -1);
    for (int i = 0; i < r; i++)
    {
      if (events[i].data.ptr == socket)
      {
        //new connection incoming
        lsqld_deal_connection(socket);
      }
      else
      {
        CONNECTION *connection = (CONNECTION*)events[i].data.ptr;

        //接收消息
        lsqld_recieve_message(connection);

        //判断客户端端口状态
        if (!connection->is_valid())
        {
          //连接不再有效，关闭端口
        }
        else
        {
          //处理客户端发送的请求
          lsqld_deal_request(events[i].data.ptr);
        }
      }
    }
  }
}

static void lsqld_deal_connection(enet_socket_t socket)
{
  int r;
  LSQLD *lsqld = LSQLD::get_instance();
  enet_t enet = lsqld->enet;
  enet_socket_t accept_socket;
  struct enet_event event;

  r = enet_socket_accept(socket, &accept_socket);

  TASK *task = TASK::alloc();
  CONNECTION *connection = CONNECTION::alloc();

  event.data.ptr = connection;
  connection->socket = accept_socket;

  r = enet_add_socket(enet, accept_socket, &event);
  task->type = TASK_CONNECTION;
  task->connection = connection;

  TASK::enqueue(task);
}

static void lsqld_recieve_message(CONNECTION connection)
{

}

static void lsqld_deal_request(CONNECTION *connection)
{
  TASK *task = TASK::alloc();

  task->type = TASK_REQUEST;

  TASK::enqueue(task);
}

void *lsqld_task_worker_thrd(void *arg)
{
  while (true)
  {
    //fetch a task
    TASK *task = TASK::dequeue();
    task_execute(task);
    TASK::free(task);
  }
}

static void lsqld_start_task_worker_thrds()
{
  uint32_t worker_number = LSQLD::get_instance()->task_worker_number;
  for (uint32_t i = 0; i < worker_number; i++)
  {
    lthrd_create(lsqld_task_worker_thrd, NULL);
  }
}

