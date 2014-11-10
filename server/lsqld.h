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
private :
  short port;    //port
  enet_t enet;   //enet of server
  enet_socket_t socket; //listenning socket
  uint32_t task_worker_number;  //worker thread number

public :
  uint32_t set_task_worker_number(uint32_t number)
  {task_worker_number = number;}


  //private member
private :
  static LSQLD *instance;
};

#endif //_LSQLD_H
