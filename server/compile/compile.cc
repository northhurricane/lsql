#include "compile.h"
#include "vm.h"

int lsql_compile_select(parse_select_t *select, VProgram **program)
{
  
  return 0;
}

int lsql_compile(parse_head_t *head, VProgram **program)
{
  switch (head->type)
  {
  case PARSE_SELECT:
    return lsql_compile_select((parse_select_t*)head, program);

  default:
    return -1;
  }

  return 0;
}

