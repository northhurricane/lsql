#ifndef LSQL_SQL_SQL_STATEMENT_H_
#define LSQL_SQL_SQL_STATEMENT_H_

#include <stdint.h>

typedef uint16_t sql_stmt_type_t;
/*用于定义SQL statement的类型*/
#define SQL_STATEMENT_NONE 0
#define SQL_STATEMENT_SELECT 1
#define SQL_STATEMENT_INSERT 2
#define SQL_STATEMENT_DELETE 3
#define SQL_STATEMENT_UPDATE 4
#define SQL_STATEMENT_CREATE_TABLE 5

#endif //LSQL_SQL_SQL_STATEMENT_H_
