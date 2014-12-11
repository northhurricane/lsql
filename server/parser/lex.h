#ifndef LSQLD_SERVER_PARSER_LEX_H_
#define LSQLD_SERVER_PARSER_LEX_H_

/*
用于声明词法分析函数
*/
#include "parser.h"

inline parse_ojbect_t *lex_integer(uint8_t *text, uint32_t length)
{
  return NULL;
}

inline parse_objec_t *lex_decimal(uint8_t *text, uint32_t length)
{
  return NULL;
}

inline parse_object_t *lex_scientific(uint8_t *text, uint32_t length)
{
  return NULL;
}
#endif //LSQLD_SERVER_PARSER_LEX_H_
