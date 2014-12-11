#ifndef LSQLD_SERVER_PARSER_LEX_H_
#define LSQLD_SERVER_PARSER_LEX_H_

/*
用于声明词法分析函数
*/
#include "parser.h"

parse_ojbect_t *lex_integer(uint8_t *text, uint32_t length);

#endif //LSQLD_SERVER_PARSER_LEX_H_
