#ifndef _LSQL_SQL_SQLDATA_OP_H_
#define _LSQL_SQL_SQLDATA_OP_H_

#include "sqltypes.h"
#include "sqldata.h"

/*
  
*/

/*
  类型转换。
  返回值：
    0表示成功。
    大于0表示带有警告
    小于0表示失败
  参数
    source_type:来源类型
    source_impl_type:来源数据类型的实现类型，如日期时间类型有计算型和broken-down类型
    source_data:源数据
    target_type:
    target_impl_type:
    target_data:
*/
int
sqldata_convert(int source_type, int source_impl_type, void *source_data
                , int target_type, int target_impl_type, void *target_data);

#endif //_LSQL_SQL_SQLDATA_OP_H_
