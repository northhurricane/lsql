#include "lsql.h"
#include "LPort.h"

extern int lsqld_socket_init();

int LPort::Init()
{
  Type t = Socket;
  switch (t)
  {
  case Socket:
    lsqld_socket_init();
    break;
  default:
    lassert(false);
  }
  return 0;
}

int LPort::Deinit()
{
  return 0;
}
