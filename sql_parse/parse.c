/*
*/

#include "lsql.tab.h"
#include "lex.h"
#include "parse.h"
#include "parse_inner.h"

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
  return NULL;
}

