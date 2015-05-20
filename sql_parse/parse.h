#ifndef LSQL_SQL_PARSE_PARSE_H_
#define LSQL_SQL_PARSE_PARSE_H_

/*
  用于进行语法分析的接口
*/

#include <stdint.h>
#include "llist_p.h"
#include "parse_def.h"

#ifdef __cplusplus
extern "C" {
#endif

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

struct parse_select_from_struct
{
  parse_head_t head;
};
typedef parse_select_from_struct parse_select_from_t;

struct parse_select_item_struct
{
  parse_head_t head;

  llist_pnode_t node;
};
typedef struct parse_select_item_struct parse_select_item_t;

struct parse_select_items_struct
{
  parse_head_t head;

  llist_p_t items;
};
typedef struct parse_select_items_struct parse_select_items_t;

struct parse_select_struct
{
  parse_head_t head;

  parse_select_items_t *items;
  parse_select_from_t *from;
};
typedef struct parse_select_struct parse_select_t;

struct parse_create_table_struct
{
  parse_head_t head;

  char *table_name;
};
typedef struct parse_create_table_struct parse_create_table_t;

/*
  成功:返回分析结果
  失败:返回NULL
*/
parse_head_t*
lsql_parse(char *sql_str, parse_error_t *error, void *heap);



#ifdef __cplusplus
}
#endif

#endif //LSQL_SQL_PARSE_PARSE_H_
