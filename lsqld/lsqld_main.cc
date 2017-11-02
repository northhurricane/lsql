#include "lsqld_comm.h"

//for test
#include "lthread.h"

int lsqld_main(int argc, char *argv[])
{
  int r = 0;

  //r = lsqld_thrd_init();

  r = lsqld_comm_init();

  while (true)
  {
    lthread_sleep(10000);
  }

  //r= lsqld_comm_deinit();

  //r = lsqld_thrd_deinit();

  return 0;
}
