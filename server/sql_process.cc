#include "sql_process.h"
#include "parser.h"
#include "stmt.h"
#include "compile.h"

sql_process_result_t
sql_process_prepare(Statement *stmt, uint8_t *sql_text, uint32_t length)
{
  sql_process_result_t result = {0};

  parse_error_t error;
  parse(NULL, &error);

  lsql_compile(NULL, NULL);

  return result;
}

void sql_process_execute(Statement *stmt)
{
  
}

