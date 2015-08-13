#ifndef LSQL_SQL_PARSE_PARSE_INNER_H_
#define LSQL_SQL_PARSE_PARSE_INNER_H_

#include "lsql.h"
#include "lex.h"
#include "parse.h"

YYSTYPE
parse_create_select_sql(void *heap
                        , YYSTYPE select_list, YYSTYPE from_option)
;

YYSTYPE
parse_create_select_item_list(void *heap, YYSTYPE select_item);

YYSTYPE
parse_add_select_item_to_list(void *heap
                              , YYSTYPE select_list, YYSTYPE select_item);


#endif //LSQL_SQL_PARSE_PARSE_INNER_H_

