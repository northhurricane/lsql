#ifndef LSQL_SQL_SQLDATA_H_
#define LSQL_SQL_SQLDATA_H_

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

/*日期时间类型定义*/
/*
  分为broken-down类型，和algorithm类型。
*/
/*
  broken-down类型的定义。也是human readable的类型
*/
struct sql_date_struct
{
  uint16_t year;
  uint8_t  month;
  uint8_t  day;
};
typedef struct sql_date_struct sql_date_t;

struct sql_time_struct
{
  uint16_t hour;
  uint16_t minute;
  uint16_t second;
  uint32_t fraction;
};
typedef struct sql_time_struct sql_time_t;

struct sql_datetime_struct
{
  sql_date_t date;
  sql_time_t time;
};
typedef struct sql_datetime_struct sql_datetime_t;
/*
  algorithm类型。也称为简短类型，用于快速计算/存储等操作
*/
/*
16b |8b   |8b
year|month|day
*/
typedef uint32_t sql_dt_t;

/*
27bits|5bits|6bits |6bits |20bits
0     |hour |minute|second|microsecond
*/
typedef uint64_t sql_tm_t;

/*
2bits|16b |4b   |5b |5b  |6b    |6b    |20b
0    |year|month|day|hour|minute|second|microsecond
*/
typedef uint64_t sql_dt_t;

#endif //LSQL_SQL_SQLDATA_H_


