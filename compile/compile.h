#ifndef LSQL_SERVER_COMPILE_COMPILE_H_
#define LSQL_SERVER_COMPILE_COMPILE_H_

/*将语法结果转换为lsql虚拟机的程序*/

#include "parse.h"
#include "vm.h"

int lsql_compile(parse_head_t *head, VProgram **program);

#endif //LSQL_SERVER_COMPILE_COMPILE_H_
