#ifndef _SQL_STATEMENT_H_
#define _SQL_STATEMENT_H_

#include <stdint.h>

/*用于定义SQL statement的类型*/
enum sql_type_enum {
  SQL_STATEMENT_NONE = 0,
  SQL_STATEMENT_INSERT = 1,
  SQL_STATEMENT_DELETE = 2,
  SQL_STATEMENT_UPDATE = 3,
  SQL_STATEMENT_SELECT = 4,
  SQL_STATEMENT_CREATE_TABLE = 5
};

typedef sql_type_enum sql_type_e;

#endif //_SQL_STATEMENT_H_
