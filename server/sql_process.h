#ifndef LSQL_SERVER_SQL_PROCESS_H
#define LSQL_SERVER_SQL_PROCESS_H

#include <stdint.h>
#include "stmt.h"

struct sql_process_result_struct
{
  int result;
};
typedef struct sql_process_result_struct sql_process_result_t;

/*从SQL语句构造在vm中执行的执行对象*/
sql_process_result_t
sql_process_build(Statement *stmt, uint8_t *sql_text, uint32_t length);

/*执行sql语句*/
void sql_process_execute(Statement *stmt);
#endif //LSQL_SERVER_SQL_PROCESS_H
