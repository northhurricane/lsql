/*
*/

#include "lsql.tab.h"
#include "parse.h"

void yyerror(char const*)
{
}

extern "C"
parse_head_t*
lsql_parse_c(const char *sql_str, parse_error_t *error
             , void *heap)
{
  //初始化词法分析
  yyparse();

  return NULL;
}

