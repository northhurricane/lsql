#ifndef LSQL_SQL_TUPLE_H_
#define LSQL_SQL_TUPLE_H_

#include "row.h"
#include "column.h"
#include "memory.h"

//元组是既有行数据，又有行数据相关的column类型定义的数据结构
struct tuple_struct
{
  Memory *memory;
  columns_def_t columns_def;
  row_structed_t row_data;
};
typedef struct tuple_struct tuple_t;

tuple_t*
tuple_create(
  columns_def_t *columns_def
);

tuple_t*
tuple_create(
  columns_def_t *columns_def,
  Memory *memory
);

void
tuple_destroy(
  columns_def_t *tuple
);


#endif //LSQL_SQL_TUPLE_H_

