#ifndef _CONN_H
#define _CONN_H

#include "enet.h"
#include "lsql.h"
#include "lmessage.h"

class SESSION;

class CONNECTION
{
public :
  static CONNECTION *allocate() {}
  static void free(CONNECTION *connection){}

public :
  SESSION *session;
  enet_socket_t socket;
  lmessage_t message;
};


#endif //_CONN_H

