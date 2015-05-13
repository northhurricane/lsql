#include "parse.h"
#include "autoheap.h"

parse_head_t*
lsql_parse(const char *sql_str, parse_error_t *error
           , AutoHeap *heap);

int main(int argc, char *argv[])
{
  char const *sel_sql = "select 1";
  AutoHeap *heap = AutoHeap::Create();
  parse_error_t error;

  lsql_parse_c(sel_sql, &error, heap);
  
  return 0;
}
