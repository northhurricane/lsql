#include "sql_process.h"
#include "parser.h"
#include "stmt.h"

void sql_process_prepare(Statement *stmt, uint8_t *sql_text, uint32_t length)
{
  parse_error_t error;
  parse(NULL, &error);
}
