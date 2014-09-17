#include "lsql.h"
#include "lsqld.h"
#include "task.h"
#include "enet.h"

static void lsqld_start_task_worker_thrds();
static void lsqld_init_net();
static void lsqld_deal_net_event();

//the purpose to place main function at first is that I wish beginner
//can locate main branch as quick as possible. 
//Also abstracting what the server do to functions help beginner
//understanding this program better
int lsqld_main(int argc, char *argv[])
{
  LSQLD.initialize(argc, argv);

  lsqld_start_task_worker_thrds();

  lsqld_init_net();

  lsqld_deal_net_event();

  return 0;
}

//reading run-time variable from cmd-line and option file
lret LSQLD::initialize(int argc, char *argv[])
{
  return LSQL_SUCCESS;
}

static void lsqld_init_net()
{
  LSQLD lsqld = LSQLD.get_instance(); 
  short port = lsqld->port;

  int r;

  enet_socket_t socket = NULL;
  r = enet_socket_create(&socket, port);
  if (r == -1)
  {
    lerror("failed to create socket");
    exit(1);
  }

  enet_t enet = NULL;
  r = enet_create(&enet, 10);
  if (r == -1)
  {
    lerror("failed to create enet");
    goto error;
  }

  r = enet_add_socket(enet, socket);
  if (r == -1)
  {
    lerror("failed to add sockedt");
    goto error;
  }

  return ;
error:
  if (socket != NULL)
    enet_socket_destroy(socket);
  if (enet != NULL)
    enet_destroy(enet);

  exit(1);
}

static void lsqld_deal_net_event()
{
#define MAXEVENTS 10
  struct enet_event events[MAXEVENTS];
  enet_socket_t socket = LSQLD->get_instance()->socket;

  int r2;
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
        //request from client
        lsqld_deal_request(events[i].data.ptr);
      }
    }
  }
}

static void lsqld_deal_connection(enet_socket_t socket)
{
  int r;
  enet_socket_t acpt_socket;

  r = enet_socket_accept(socket, &acpt_socket);
  r = enet_add_socket(enet, acpt_socket);

  TASK *task = TASK->alloc();
  struct enet_event event;
  event.data.ptr = &task->connection;
  task_connection_build(task, socket, &event);
  TASK->enqueue(task);
}

static void lsqld_deal_request(void *socket_data)
{
  CONNECTION *connection = (CONNECTION*)socket_data;
  SESSION *session = connection->session;
  TASK *task = connection->task;
}

static void lsqld_start_task_worker_thrds()
{
}

TASK *lsqld_fetch_task()
{
  return NULL;
}

void *lsqld_task_worker_thrd(void *arg)
{
  while (true)
  {
    //fetch a task
  }
}

