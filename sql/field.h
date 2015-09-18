#ifndef LSQL_SQL_FIELD_H_
#define LSQL_SQL_FIELD_H_

#include "sqltypes.h"
#include "sqldata.h"
/*
  行数据的每列的内存对象
*/

struct field_struct
{
};
typedef field_struct field_t;

struct field_int_struct : public field_t
{
  sql_int_t data;
};
typedef field_int_struct field_int_t;

struct field_char_struct : public field_t
{
  sql_char_t data;
};
typedef field_char_struct field_char_t;

struct field_varchar_struct : public field_t
{
  sql_varchar_t data;
};
typedef field_varchar_struct field_varchar_t;


#endif //LSQL_SQL_FIELD_H_

