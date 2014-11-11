#ifndef _LSQLD_H
#define _LSQLD_H

#include "lsql.h"
#include "enet.h"

int lsqld_main(int argc, char *argv[]);

//record lsqld global variables
class LSQLD
{
public :
  static LSQLD *GetInstance() {return instance_;}
  lret InitializeArguements(int argc, char *argv[]);

private :
  enet_t enet_;   //enet of server
  enet_socket_t socket_; //listenning socket

public :
  enet_t enet() {return enet_;}
  void set_enet(enet_t enet) {enet_ = enet;}
  enet_socket_t socket() { return socket_; }
  void set_socket(enet_socket_t socket) {socket_ = socket;}

private :
  static LSQLD *instance_;
  static LSQLD *Constructor();
};

#endif //_LSQLD_H
