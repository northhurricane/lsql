#ifndef _LSQL_SQL_SQLDATA_OP_H_
#define _LSQL_SQL_SQLDATA_OP_H_

#include "sqltypes.h"
#include "sqldata.h"

int
sqldata_convert(int source_type, int source_impl_type, void *source_data
                , int target_type, int target_impl_type, void *target_data);

#endif //_LSQL_SQL_SQLDATA_OP_H_
