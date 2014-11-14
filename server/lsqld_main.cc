#include "lsqld.h"
#include "task.h"
#include "enet.h"
#include "conn.h"
#include "lsqld_thread.h"

static void lsqld_init_net();
static void lsqld_deal_net_event();
static void lsqld_create_shutdown_thread();

//the purpose to place main function at first is that I wish beginner
//can locate main branch as quick as possible. 
//Also abstracting what the server do to functions help beginner
//understanding this program better
int lsqld_main(int argc, char *argv[])
{
  LSQLD::GetInstance()->InitializeArguements(argc, argv);

  //所有线程的创建依赖于ThreadManager的初始化
  ThreadManager::Initialize();
  TaskManager::Initialize();

  lsqld_create_shutdown_thread();

  lsqld_init_net();

  lsqld_deal_net_event();

  TaskManager::Deinitialize();
  ThreadManager::Deinitialize();

  return LSQL_SUCCESS;
}

static void lsqld_init_net()
{
  LSQLD *lsqld = LSQLD::GetInstance(); 
  short port = 5966;

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

  lsqld->set_enet(enet);
  lsqld->set_socket(socket);

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
  LSQLD *lsqld = LSQLD::GetInstance();
  enet_t enet = lsqld->enet();
  enet_socket_t socket = lsqld->socket();

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
        Connection *connection = (Connection*)events[i].data.ptr;

        //接收消息
        //lsqld_recieve_message(connection);

        //判断客户端端口状态
        //if (!connection->is_valid())
        if (false)
        {
          //连接不再有效，关闭端口
        }
        else
        {
          //处理客户端发送的请求
          //lsqld_deal_request(events[i].data.ptr);
        }
      }
    }
  }
}

//处理新连接
static void lsqld_deal_connection(enet_socket_t socket)
{
  int r;
  LSQLD *lsqld = LSQLD::GetInstance();
  enet_t enet = lsqld->enet();
  enet_socket_t accept_socket;
  struct enet_event event;

  r = enet_socket_accept(socket, &accept_socket);

  Connection *connection = new Connection();
  ConnectionManager::Add(connection);
  Vio *vio = new VioEnet(accept_socket);
  connection->set_vio(vio);
  event.data.ptr = connection;

  r = enet_add_socket(enet, accept_socket, &event);
}

//关闭服务线程
static void* lsqld_shutdown_thread(void *para)
{
  while (true)
  {
  }
  return NULL;
}

static void lsqld_create_shutdown_thread()
{
}
