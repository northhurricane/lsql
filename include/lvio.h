#ifndef LSQL_INCLUDE_VIO_H_
#define LSQL_INCLUDE_VIO_H_

#include "enet.h"

class Vio
{
public :
  virtual int Recieve(void *buf, int len) = 0;
  virtual int Send(const void *buf, int len) = 0;
};

class VioEnet : public Vio
{
private :
  enet_socket_t socket_;

public :
  VioEnet (enet_socket_t socket)
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
