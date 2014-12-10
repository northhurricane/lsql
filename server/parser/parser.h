#ifndef LSQL_SERVER_PARSER_PARSER_H_
#define LSQL_SERVER_PARSER_PARSER_H_

#include "lsql.h"

/*
语法分析的结果不采用递归的语法树的方式，而是采用与SQL定义的巴克斯范式接近的/便于在内存中观察的方式
如insert into tablename (f1, f2, f3) values (1, 2, 3);将在结构中被记录为如下
fake struct
{
  char *tablename;
  list<char*> columns_name;
  list<value> values;
};
每一个被单独执行的sql语句（DML/DDL等）都将以这种方式存储，期望存储本身将可以直观的还原语句的内容，而不是令人生畏的语法嵌套表达
*/

/* 
1、用来记录语法分析时词法分析器和语法分析器之间交互信息的信息。
  如词法分析器返回给语法分析器的字符常量的具体信息，‘abc’
2、当前语法/词法分析的所需的环境信息
  如是否大小写敏感等
*/
struct parse_extra_struct
{
};
typedef struct parse_extra_struct parse_extra_t;

struct parse_error_struct
{
  uint32_t error_line_number;
  uint32_t error_colume_number;
  uint32_t error_position;
};
typedef struct parse_error_struct parse_error_t;

/* 所有语法元素结构的第一个成员变量都是该类型，从而作为统一返回的内容 */
struct parse_object_struct
{
  uint32_t type;
};
typedef struct parse_object_struct parse_object_t;

struct parse_create_table_struct
{
  parse_object_t head;
};
typedef struct parse_create_table_struct parse_create_table_t;

struct parse_insert_struct
{
  parse_object_t head;
};
typedef struct parse_insert_struct parse_insert_t;

#define YYSTYPE parse_object_t*

lret parse(parse_object_t **result, parse_error_t *error);

#endif //LSQL_SERVER_PARSER_PARSER_H_

