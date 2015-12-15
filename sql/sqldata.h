#ifndef LSQL_SQL_SQLDATA_H_
#define LSQL_SQL_SQLDATA_H_

#include "lsql_limit.h"
/*
与sql type进行对应。
*/

//LSQL_TYPE_INT
struct sql_int_struct
{
  union {
    int32_t  sv; //有符号
    uint32_t uv; //无符号
  };
  uint8_t sign;  //符号
};
typedef struct sql_int_struct sql_int_t;

//LSQL_TYPE_SMALLINT
struct sql_smallint_struct
{
  union {
    int16_t  sv; //有符号
    uint16_t uv; //无符号
  };
  uint8_t sign;
};
typedef struct sql_smallint_struct sql_smallint_t;

//LSQL_TYPE_TINYINT
struct sql_tinyint_struct
{
  union {
    int8_t  sv; //有符号
    uint8_t uv; //无符号
  };
  uint8_t sign; //符号
};
typedef struct sql_tinyint_struct sql_tinyint_t;

//LSQL_TYPE_BIGINT
struct sql_bigint_struct
{
  union {
    int64_t  sv;
    uint64_t uv;
  };
  uint8_t sign;
};
typedef struct sql_bigint_struct sql_bigint_t;

/*char。空个填充*/
struct sql_char_struct
{
  uint16_t len;  //长度
};
typedef struct sql_char_struct sql_char_t;

/*varchar*/
struct sql_varchar_struct
{
  uint16_t len;
};
typedef struct sql_varchar_struct sql_varchar_t;



#endif //LSQL_SQL_SQLDATA_H_


