#include "lsql.lex.h"
#include "lex.h"
#include <stdlib.h>

struct lex_struct
{
  yyscan_t scanner;
};
typedef struct lex_struct lex_t;

hlex_t
lex_init(char *input)
{
  lex_t *hlex = (lex_t*)malloc(sizeof(lex_t[1]));

  if (hlex == NULL)
    return NULL;

  lsqllex_init(&hlex->scanner);

  return hlex;
}

/*
  为yyparse提供词法分析的接口
*/
int yylex(YYSTYPE *lvalp, hlex_t hlex)
{
  yyscan_t scanner;
  lex_t *lex = (lex_t*)hlex;

  scanner = lex->scanner;

  lsqllex(scanner);

  return 0;
}

void
lex_destroy(hlex_t hlex)
{
  yyscan_t scanner;
  lex_t *lex = (lex_t*)hlex;

  scanner = lex->scanner;

  lsqllex_destroy(scanner);

  free(lex);
}
