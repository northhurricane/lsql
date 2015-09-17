#ifndef LSQL_SQL_TUPLE_H_
#define LSQL_SQL_TUPLE_H_

#include "row.h"
#include "column.h"

//元组是既有行数据，又有行数据相关的column类型定义的数据结构
struct tuple_struct
{
  columns_def_t columns_def;
  row_structed_t data;
};

typedef struct tuple_struct tuple_t;

#endif //LSQL_SQL_TUPLE_H_

