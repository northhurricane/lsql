#ifndef LSQL_SERVER_COMPILE_COMPILE_H_
#define LSQL_SERVER_COMPILE_COMPILE_H_

#include "parse.h"
#include "vm.h"

int compile(parse_head_t *head, VProgram **program);

#endif //LSQL_SERVER_COMPILE_COMPILE_H_
