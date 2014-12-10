#ifndef LSQL_SERVER_SQL_PROCESS_H
#define LSQL_SERVER_SQL_PROCESS_H

#include <stdint.h>
#include "stmt.h"

void sql_process_prepare(Statement *stmt, uint8_t *sql_text, uint32_t length);

#endif //LSQL_SERVER_SQL_PROCESS_H
