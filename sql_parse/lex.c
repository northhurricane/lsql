#include "lsql.lex.h"
#include "lsql.tab.h"
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

int mock_select()
{
  static int count = 0;
  switch (count)
  {
  case 0:
  {
    count++;
    return KW_SELECT;
  }
  case 1:
  {
    count++;
    return LT_INTEGER;
  }
  default:
  {
    count = 0;
    return 0;
  }
  }
}

/*
  为yyparse提供词法分析的接口
*/
int yylex(YYSTYPE *lvalp, hlex_t hlex)
{
  yyscan_t scanner;
  lex_t *lex = (lex_t*)hlex;
  int token;

  if (1)
    return mock_select();

  scanner = lex->scanner;

  token = lsqllex(scanner);
  if (token == TOKEN_ID)
  {
    /*对id进行检查*/
    return TOKEN_ID;
  }

  return token;
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
