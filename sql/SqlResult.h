#ifndef LSQL_SQL_SQL_RESULT_H_
#define LSQL_SQL_SQL_RESULT_H_

#include <stdint.h>

class Rowset;

//SQL执行后得到的结果，分为两种类型。一个是行集结果（rowset result），一个是影响行数结果（row count result）
class SqlResult
{
public :
  enum Type {Invalid = 0, Rowset = 1, RowCount = 2};
  Type type() { return type_; }

private :
  Type type_;

  uint8_t row_count_;
  Rowset *rowset;
};

#endif //LSQL_SQL_SQL_RESULT_H_
