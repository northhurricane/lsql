#ifndef LSQL_SQL_SQLDATA_H_
#define LSQL_SQL_SQLDATA_H_

#include "lsql_limit.h"
/*
  sqldata是用于存储sql数据类型的结构
  如：create table (f1 int);
  int对应的是sql_int_struct的存储
*/

/*int*/
struct sql_int_struct
{
  uint8_t v;
};
typedef struct sql_int_struct sql_int_t;

/*char。空个填充*/
struct sql_char_struct
{
  uint16_t l;  //长度
  uint8_t v[LSQL_DATA_MAX_SPACE]; //值
};
typedef struct sql_char_struct sql_char_t;

/*varchar*/
struct sql_varchar_struct
{
  uint16_t l;
  uint8_t v[LSQL_DATA_MAX_SPACE];
};
typedef struct sql_varchar_struct sql_varchar_t;



#endif //LSQL_SQL_SQLDATA_H_


