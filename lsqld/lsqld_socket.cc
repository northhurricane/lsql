#include "lsqld_thrd.h"
#include "LConn.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include "lsqld_worker.h"

//test
#define BACKLOG 10    /* 最大同时连接请求数 */
#define SERVPORT 9527 /* 服务器监听端口号 */
#define EPOLLHINT 10  /* create_epoll参数 */
#define MAX_EVENTS 10

#include "lthread.h"


static int sockfd;
static int epollfd;

static int
socket_add_to_epoll(LConn *conn, int client_sockfd)
{
  struct epoll_event ev;

  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = client_sockfd;
  ev.data.ptr = conn;

  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client_sockfd, &ev) == -1)
  {
    //perror("epoll_ctl failed add client connected socket");
    return -1;
  }
}

static void
socket_remove_from_epoll(struct epoll_event *event)
{
  struct epoll_event tmp_event = {0, {0}};
  int client_sockfd = event->data.fd;
  LConn *conn = (LConn*)event->data.ptr;

  int r = epoll_ctl(epollfd, EPOLL_CTL_DEL, client_sockfd, &tmp_event);
  if (r != 0)
  {
  }
  close(event->data.fd);
  LConnManager::DestroyConn(conn);
}

static int
socket_read(LConn *conn, int client_sockfd)
{
  void * buff = NULL;
  int buff_size = 0;
  int msg_len = 0;
  buff = conn->GetBuffer();
  buff_size = conn->GetBufferSize();
  msg_len = recv(client_sockfd, buff, buff_size, 0);
  if (msg_len > buff_size)
  {
    int nsize = msg_len * 2;
    buff = conn->GetBuffer(nsize);
  }
  conn->SetMsgLen(msg_len);
  return 0;
}

static void*
socket_epoll_thrd(void *)
{
  bool quit = false;
  int nfds = 0;
  struct epoll_event events[MAX_EVENTS];
  while (true)
  {
    nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    //check alive,read data and add to work list
    if (quit)
      break;
    for (int i = 0; i < nfds; i++)
    {
      if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP)
          || (!(events[i].events & EPOLLIN)))
      {
        socket_remove_from_epoll(events + i);
        continue;
      }
      else
      {
        //process income event
        LConn *conn = (LConn*)events[i].data.ptr;
        socket_read(conn, events[i].data.fd);
        worker_msg_task_enqueue(conn);
      }
    }
  }
}

static int
socket_process_connection(int client_sockfd)
{
  LConn *conn = LConnManager::CreateConn();
  if (conn == NULL)
  {
    return -1;
  }
  int r = socket_add_to_epoll(conn, client_sockfd);
  if (r)
  {
    LConnManager::DestroyConn(conn);
    return -1;
  }
  return 0;
}

static void*
socket_listen_thrd(void *)
{
  struct sockaddr_in remote_addr;
  socklen_t sin_size = sizeof(struct sockaddr_in);
  int client_sockfd;
  bool quit=false;

  while (true)
  {
    client_sockfd = accept(sockfd, (struct sockaddr*) &remote_addr, &sin_size);
    if (quit)
      break;
    if (client_sockfd)
    {
      //create connection object LConn add client socket to epoll
      socket_process_connection(client_sockfd);
    }
  }
}

static
int socket_init()
{
  struct sockaddr_in my_addr;

  if ((sockfd = socket(AF_INET,  SOCK_STREAM,  0)) == -1)
  {
    return (-1);
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(SERVPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;

  bzero(&(my_addr.sin_zero), 8);
  if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == 1)
  {
    return (-1);
  }

  if (listen(sockfd,  BACKLOG) == -1)
  {
    return (-1);
  }
}

static
int epoll_init()
{
  epollfd = epoll_create(EPOLLHINT);
}

int lsqld_socket_init()
{
  int r = 0;
  r = socket_init();
  if (r)
    return r;
  r = epoll_init();
  //create listen thread
  lthread_t thrd;
  r = lthread_create(socket_listen_thrd, NULL, &thrd);
  /*lsqld_thrd_create(socket_listen_thrd);
  lsqld_thrd_create(socket_epoll_thrd);*/
  return 0;
}

int lsqld_socket_deint()
{
  //close(sockfd);
}
