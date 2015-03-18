#ifndef LSQL_SQL_PARSE_PARSE_H_
#define LSQL_SQL_PARSE_PARSE_H_

#include "lsql.h"

struct parse_error_struct
{
  uint4 line;
};
typedef struct parse_error_struct parse_error_t;

struct parse_head_struct
{
  uint4_t type;
};
typedef struct parse_head_struct parse_head_t;

struct parse_create_table_struct
{
  parse_head_t head;

  char *table_name;
};
typedef struct parse_create_table_struct parse_create_table_t;

class AutoHeap;

/*
  success:return resut
  fail:return NULL
*/
parse_heat_t*
lsql_parse(const char *sql_str, parse_error_t *error, AutoHeap *heap);

#endif //LSQL_SQL_PARSE_PARSE_H_
