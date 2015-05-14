#ifndef LSQL_SQL_PARSE_PARSE_INNER_H_
#define LSQL_SQL_PARSE_PARSE_INNER_H_

#include "parse.h"

YYSTYPE
parse_create_select_sql(void *heap
                        , YYSTYPE select_list, YYSTYPE from_option)
;


#endif //LSQL_SQL_PARSE_PARSE_INNER_H_

