#ifndef LSQL_SQL_PARSE_H_
#define LSQL_SQL_PARSE_H_

#include <stdint.h>
#include "lsql.tab.h"

typedef void *hlex_t;

hlex_t lex_init(char *input);
void lex_destroy(hlex_t hlex);
int yylex(YYSTYPE *lvalp, hlex_t hlex);

#endif //LSQL_SQL_PARSE_H_
