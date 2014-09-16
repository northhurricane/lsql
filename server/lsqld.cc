#include "lsqld.h"

static void lsqld_init_net()
{
  LSQLD.get_instance()->port;
}

static void lsqld_deal_net_event()
{
}

int lsqld_main(int argc, char *argv)
{
  LSQLD.initialize();

  lsqld_init_net();

  lsqld_deal_net_event();

  return 0;
}

//reading run-time variable from cmd-line and option file
lret LSQLD::initialize(int argc, char *argv)
{
  return LSQL_SUCCESS;
}

