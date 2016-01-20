#ifndef LSQL_COMM_PORT_H_
#define LSQL_COMM_PORT_H_

#include "enet.h"

class CommPort
{
public :
  virtual int Recieve(void *buf, int len) = 0;
  virtual int Send(const void *buf, int len) = 0;
};

class EnetPort : public CommPort
{
private :
  enet_socket_t socket_;

public :
  EnetPort (enet_socket_t socket)
  {
    socket_ = socket;
  }

  int Recieve(void *buf, int len)
  {
    return enet_socket_recv(socket_, buf, len, 0);
  }

  int Send(const void *buf, int len)
  {
    return enet_socket_send(socket_, buf, len, 0);
  }
};


#endif //LSQL_INCLUDE_VIO_H_
