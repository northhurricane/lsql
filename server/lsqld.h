#ifndef _LSQLD_H
#define _LSQLD_H

#include "enet.h"

int lsqld_main(int argc, char *argv);

class LSQLD
{
  //public function
public :
  lret initialize(int argc, char *argv[]);
  LSQLD *get_instance() {return m_instance;}

  //public member
public :
  short port;
  enet_t enet;

  //private member
private :
  LSQLD *instance;
};

#endif //_LSQLD_H
