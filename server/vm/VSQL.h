#ifndef LSQL_VM_VSQL_H_
#define LSQL_VM_VSQL_H_

#include "sql_statement.h"
/*
SELECT/INSERT/DELETE/UPDATE/CREATE等SQL的基类，每个sql由VFunction的组合调用完成工作
VSQL是作为VFunction
*/
class VFunction;

class VSQL
{
public :
  VSQL() { entrance_ = NULL; }
  VFunction *entrance() { return entrance_; }
  void set_entrance(VFunction *entrance) { entrance_ = entrance; }
  sql_stmt_type_t stmt_type() { return stmt_type_; }

protected :
  //入口函数
  VFunction *entrance_;
  //SQL的类型
  sql_stmt_type_t stmt_type_;
};


#endif //LSQL_VM_VSQL_H_
