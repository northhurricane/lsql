#include "lsqld_comm.h"
#include "LPort.h"


int lsqld_comm_init()
{
  int r = 0;

  r = LPort::Init();

  return 0;
}

int lsqld_comm_deinit()
{
  return 0;
}

