#ifndef _LSQLD_H
#define _LSQLD_H

#include "lsql.h"
#include "enet.h"

int lsqld_main(int argc, char *argv[]);

//record lsqld global variables
class LSQLD
{
  //public function
public :
  static lret initialize(int argc, char *argv[]);
  static LSQLD *get_instance() {return instance;}

  //public member
public :
  short port;    //port
  enet_t enet;   //socket of server
  enet_socket_t socket; //listenning socket
  uint32_t task_worker_number;  //worker thread number

  //private member
private :
  static LSQLD *instance;
};

#endif //_LSQLD_H
