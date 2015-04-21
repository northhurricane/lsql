#ifndef _LSQL_H
#define _LSQL_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

//function call return. 
typedef int32_t lret;

#define LSQL_SUCCESS (0)
#define LSQL_ERROR   (-1)
#define LSQL_WARN    (1)

//inline bool lsql_succeeded(lret r) { return r >= 0; }

inline void lerror(const char *emsg) {}

inline void lexit(int i) { exit(i); }

inline void lsql_stop()
{
  int i = 0;
  //printf("%d", i);
}

inline void lassert(bool b)
{
  lsql_stop();
  assert(b);
}

#define LEND 0

#ifndef NULL
#define NULL 0
#endif

#endif //_LSQL_H
