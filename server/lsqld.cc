#include "lsqld.h"

LSQLD *LSQLD::instance_ = LSQLD::Constructor();
LSQLD *LSQLD::Constructor()
{
  LSQLD *instance = new LSQLD();
  return instance;
}


//reading run-time variable from cmd-line and option file
lret LSQLD::InitializeArguements(int argc, char *argv[])
{
  return LSQL_SUCCESS;
}

