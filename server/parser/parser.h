#ifndef LSQL_SERVER_PARSER_PARSER_H_
#define LSQL_SERVER_PARSER_PARSER_H_

#include <stdint.h>

/* 所有语法元素结构都使用该结构作为第一个变量的类型 */
struct parse_head_struct
{
  uint32_t type;
};
typedef struct parse_head_struct parse_head_t;


#endif //LSQL_SERVER_PARSER_PARSER_H_
