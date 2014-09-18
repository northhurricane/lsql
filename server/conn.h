#ifndef _CONN_H
#define _CONN_H

#include "enet.h"
class SESSION;

class CONNECTION
{
public :
  static CONNECTION *alloc() {}
  static void free(CONNECTION *connection){}

public :
  SESSION *session;
  enet_socket_t socket;
};

#endif //_CONN_H

