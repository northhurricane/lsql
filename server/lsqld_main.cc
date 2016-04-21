#include "lsqld.h"
#include "enet.h"
#include "conn.h"
#include "work_threads.h"
#include "LComm.h"

static void lsqld_init_vm();
static void lsqld_deinit_vm();
static void lsqld_wait_for_deinit_ready();
static void lsqld_init_ldb();
static void lsqld_deinit_ldb();
static int lsqld_init_comm();
static void lsqld_deal_comm_event();

//the purpose to place main function at first is that I wish beginner
//can locate main branch as quick as possible. 
//Also abstracting what the server do to functions help beginner
//understanding this program better
int lsqld_main(int argc, char *argv[])
{
  LSQLD::GetInstance()->InitializeArguements(argc, argv);

  //初始化lsqld进程
  //所有线程的创建依赖于ThreadManager的初始化，必须第一个初始化
  work_threads_init();

  lsqld_init_vm();

  lsqld_init_ldb();

  //lsqld_init_comm();

  //初始化完成，处理通信事件
  lsqld_deal_comm_event();

  //关闭所有端口，不再处理用户请求，进行资源的销毁
  lsqld_wait_for_deinit_ready();

  lsqld_deinit_ldb();

  lsqld_deinit_vm();

  work_threads_deinit();

  return LSQL_SUCCESS;
}

static int lsqld_init_comm()
{
  int r;
  r = LComm::Initialize();
  if (r < 0)
  {
    //记录错误日志
  }
  return r;
}

static void lsqld_deal_comm_event()
{
  LComm *comm = lcomm_get();
  lcomm_event_t events[LCOMM_MAX_EVENT_WAIT];
  lcomm_event_t *event;
  int num;

  while (true)
  {
    if (comm->Closed())
      break;

    num = comm->Wait(events, LCOMM_MAX_EVENT_WAIT);
    if (num <= 0)
    {
      //错误处理
    }
    for (int i = 0; i < num; i++)
    {
      event = events + i;
      //处理事件
      if (event->get_type() == LCOMM_EVENT_CONNECT)
      {
        //处理连接
        connect_task_enqueue(event->get_port());
      }
      else if (event->get_type() == LCOMM_EVENT_MESSAGE)
      {
        //处理消息
      }
      else
      {
        //处理断开
        lassert(event->get_type() == LCOMM_EVENT_DISCONNECT);
      }
    }
  }
}

#ifdef _COMPILE_IT_
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
static void lsqld_deal_message(Connection *connection);

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
        connection->Recieve();

        //判断客户端端口状态
        if (!connection->Valid())
        {
          //连接不再有效，关闭端口
          delete connection;
        }
        else
        {
          //处理客户端发送的请求
          lsqld_deal_message(connection);
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
  //Vio *vio = new VioEnet(accept_socket);
  //connection->set_vio(vio);
  event.data.ptr = connection;

  r = enet_add_socket(enet, accept_socket, &event);
}

static void lsqld_deal_message(Connection *connection)
{
}

#endif //_COMPILE_IT_

static void lsqld_init_vm()
{
}

static void lsqld_deinit_vm()
{
}

static void lsqld_wait_for_deinit_ready()
{
}

static void lsqld_init_ldb()
{
}

static void lsqld_deinit_ldb()
{
}

