#ifndef LSQL_SERVER_VM_VPROGRAM_H
#define LSQL_SERVER_VM_VPROGRAM_H

class VMSQL;

/*每条sql将被转化为一个program。每个program都由若干的function组成*/
class VProgram
{
public :
  void Run(VProcess *process);

  uint32_t function_amount() {return function_amount_;}
  bool Link(VFunction *entrance);

  /*
    将生成的可运行的SQL对象进行绑定
   */
  bool BindSql(VMSQL *sql);
  VFunction *entrance() { return entrance_; }
  VProgram();

private :
  uint32_t  function_amount_; //程序中的函数个数
  VFunction *entrance_;
  VMSQL *vmsql_;

  bool GenerateFunctionSerial(VFunction *function);

};


#endif //LSQL_SERVER_VM_VPROGRAM_H
