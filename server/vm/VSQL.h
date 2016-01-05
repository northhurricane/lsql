#ifndef LSQL_VM_VSQL_H_
#define LSQL_VM_VSQL_H_

/*
SELECT/INSERT/DELETE/UPDATE/CREATE等SQL的基类，每个sql由VFunction的调用完成工作
*/
class VSQL
{
public :
  VSQL();
  void Run(VProcess *process);
  uint32_t function_amount() {return function_amount_;}
  bool Link();
  VFunction *entrance() { return entrance_; }
  void set_entrance(VFunction *entrance) { entrance_ = entrance; }
  sql_stmt_type_t stmt_type() { return stmt_type_; }

protected :
  void set_stmt_type(sql_stmt_type_t type) { stmt_type_ = type; }

private :
  //完成SQL的函数个数
  uint16_t  function_amount_;
  //入口函数
  VFunction *entrance_;
  //生成函数的序列号
  bool GenerateFunctionSerial(VFunction *function);

  //SQL的类型
  sql_stmt_type_t stmt_type_;
  //每条SQL都有自己的结果。DML的SELECT的结果为
  VSqlResult *result_;
};


#endif //LSQL_VM_VSQL_H_
