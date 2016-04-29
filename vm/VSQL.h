#ifndef LSQL_VM_VSQL_H_
#define LSQL_VM_VSQL_H_

#include "sql_statement.h"
#include "VFunction.h"
/*
SELECT/INSERT/DELETE/UPDATE/CREATE等SQL的基类
*/
class VSQL : public VFunction
{
public :
  VSQL() { entrance_ = NULL; }
  sql_type_e get_sql_type() { return sql_type_; }

protected :
  //SQL的类型
  sql_type_e sql_type_;
};


#endif //LSQL_VM_VSQL_H_
