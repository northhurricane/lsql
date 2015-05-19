/*
*/

#include "lsql.tab.h"
#include "parse_inner.h"
#include "autoheap_c.h"

void yyerror(void *heap, void *hlex, char const* msg)
{
}

parse_head_t*
lsql_parse(char *sql_str, parse_error_t *error
             , void *heap)
{
  //初始化词法分析
  hlex_t hlex;

  hlex = lex_init(sql_str);
  
  yyparse(heap, hlex);

  lex_destroy(hlex);

  return NULL;
}

/*为lsql.y提供的内部语法分析函数*/
YYSTYPE
parse_create_select_sql(void *heap
                        , YYSTYPE select_list, YYSTYPE from_option)
{
  parse_select_t *select = NULL;

  select = (parse_select_t*)autoheap_alloc(heap, sizeof(parse_select_t[1]));

  return select;
}

