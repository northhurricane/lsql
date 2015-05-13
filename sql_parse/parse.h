#ifndef LSQL_SQL_PARSE_PARSE_H_
#define LSQL_SQL_PARSE_PARSE_H_

/*
  用于
*/

#include "lsql.h"

struct parse_error_struct
{
  uint32_t line;
};
typedef struct parse_error_struct parse_error_t;

struct parse_head_struct
{
  uint32_t type;
};
typedef struct parse_head_struct parse_head_t;

struct parse_select_struct
{
  parse_head_t head;
};
typedef struct parse_select_struct parse_select_t;

struct parse_create_table_struct
{
  parse_head_t head;

  char *table_name;
};
typedef struct parse_create_table_struct parse_create_table_t;

class AutoHeap;

/*
  成功:返回分析结果
  失败:返回NULL
*/
parse_head_t*
lsql_parse(const char *sql_str, parse_error_t *error
           , AutoHeap *heap);

#endif //LSQL_SQL_PARSE_PARSE_H_
