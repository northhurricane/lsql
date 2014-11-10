#include "lthread.h"

#include <list>

using namespace std;

list<LTHREAD*> th

lret
lthread_create(LTHREAD *lthread)
{
  int r = thread_create(lthread->func, lthread->para, &lthread->thread);

  if (r == THREAD_SUCCESS)
    return LSQL_SUCCESS;
  return LSQL_ERROR;
}
