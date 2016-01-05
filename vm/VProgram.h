#ifndef LSQL_VPROGRAM_H
#define LSQL_VPROGRAM_H

class VMSQL;

/*
虚拟程序
1、VMSQL可以看作是C中编译好的obj文件组合，转换为VProgram相当于进行一次链接。
2、链接的目的是为VSQL中的各个函数生成了在虚拟程序中的位置信息。这些位置信息在虚拟程序运行时，将提供定位功能，也就是通过位置信息找到保存虚拟函数运行信息。
3、运行时，VProgram的内容是保持不变的。这样就可以确保同一个虚拟程序，可以同时执行。
*/
class VProgram
{
public :
  /*进行代码运行*/
  void Run(VProcess *process);

  /*VSQL中的函数总数*/
  uint32_t function_amount() {return function_amount_;}
  /*将生成的可运行的SQL对象进行绑定*/
  bool Bind(VMSQL *sql);

  VProgram();

private :
  uint32_t  function_amount_; //程序中的函数个数
  VMSQL *vmsql_;

  /*根据VSQL对象完成*/
  bool GenerateFunctionSerial(VFunction *function);
  /*对VSQL进行连接*/
  bool Link(VFunction *entrance);
};


#endif //LSQL_VPROGRAM_H
