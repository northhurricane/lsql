#ifndef _LSQL_H
#define _LSQL_H

//function call return. 
typedef int lret;

#define LSQL_SUCCESS (0)
#define LSQL_ERROR   (-1)

inline bool lsql_succeeded(lret r) { return r >= 0; }

#define NULL 0

#endif //_LSQL_H
