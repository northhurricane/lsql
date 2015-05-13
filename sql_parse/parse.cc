#include "parse.h"
#include "autoheap.h"

extern "C"
parse_head_t*
lsql_parse_c(const char *sql_str, parse_error_t *error
             , void *heap);


parse_head_t*
lsql_parse(const char *sql_str, parse_error_t *error
           , AutoHeap *heap)
{
  return lsql_parse_c(sql_str, error, heap);
}
