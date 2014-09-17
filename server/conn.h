#ifndef _CONN_H
#define _CONN_H

#include "enet.h"
class TASK;
class SESSION;

class CONNECTION
{
public :
  static CONNECTION *alloc();
  static void free(Connection *connection);

public :
  TASK *task;
  SESSION *session;
  enet_socket_t socket;
};

#endif //_CONN_H

