#ifndef _CONN_H
#define _CONN_H

#include "enet.h"
#include "lsql.h"
#include "lmessage.h"

class Session;

class Connection
{
public :
  Session *session;
  enet_socket_t socket;
};


#endif //_CONN_H

