#include "parse.h"
#include "autoheap.h"

int main(int argc, char *argv[])
{
  char *sel_sql = "select 1";
  AutoHeap *heap = AutoHeap::Create();
  parse_error_t error;

  lsql_parse(sel_sql, &error, heap);
  
  return 0;
}
