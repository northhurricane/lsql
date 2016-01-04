#ifndef LSQL_VPROGRAM_H
#define LSQL_VPROGRAM_H

class VMSQL;

/*
VMSQL可以看作是C中编译好的obj文件，转换为VProgram相当于进行一次链接。
为各个函数生成了在虚拟程序中的位置信息，在虚拟程序的运行中，这些位置信息将提供和虚拟函数对应的定位功能。
*/
class VProgram
{
public :
  /*进行代码运行*/
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

  /*根据VSQL对象完成*/
  bool GenerateFunctionSerial(VFunction *function);

};


#endif //LSQL_VPROGRAM_H
