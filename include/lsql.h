#ifndef _LSQL_H
#define _LSQL_H

#include <stdint.h>
#include <stdlib.h>

//function call return. 
typedef int lret;

#define LSQL_SUCCESS (0)
#define LSQL_ERROR   (-1)

//inline bool lsql_succeeded(lret r) { return r >= 0; }

inline void lerror(const char *emsg) {}

inline void lexit(int i) { exit(i); }

#ifndef NULL
#define NULL 0
#endif

#endif //_LSQL_H
