#include "lsqld_thrd.h"
#include "LConn.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

//test
#define BACKLOG 10    /* 最大同时连接请求数 */
#define SERVPORT 9527 /* 服务器监听端口号 */
#include "lthread.h"


static int sockfd;
static int epollfd;

static void*
socket_epoll_thrd(void *)
{
  bool quit = false;
  while (true)
  {
    //    nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    //check alive,read data and add to work list
    if (quit)
      break;
  }
}

static void
socket_accept_connection(int sock)
{
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
      socket_accept_connection(client_sockfd);
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

int lsqld_socket_init()
{
  int r = 0;
  r = socket_init();
  if (r)
    return r;
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
