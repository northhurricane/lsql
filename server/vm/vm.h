#ifndef LSQL_SERVER_VM_VM_H_
#define LSQL_SERVER_VM_VM_H_

#include <list>

/* 
设计目标
每一个SQL语句的完成都是由一些列函数调用完成的。
sql的执行被分解为一系列函数的执行。
sql的优化就变成函数的优化，这包括函数构成的优化，函数实现的优化。
功能的增加就变成函数的增加
目标是使优化变得更易读/易写/易优化

函数式语言lisp是通过函数的嵌套完成功能的开发。在其实现中链表和函数是很重要
(functionA argument_functionA argument_functionB)是lisp的调用方式
在functionA完成之前，argument_functionA/B必须执行完成
所以，控制就变为函数的调用和结果保存，然后当前函数的执行。

执行的控制变为函数调用的控制。调用函数，函数返回，传入参数，返回结果，函数执行
每个函数只关注传入的参数/被调用函数的返回和自身的逻辑
函数调用，
函数返回，
传入参数，
返回结果，
函数执行，

需要callstack来记录调用堆栈和每层函数执行当前状态。调用堆栈用于函数返回时找到调用者，恢复每层函数的当前状态用于继续执行后续的操作。

*/

using namespace std;

class VFunction;
typedef list<VFunction*> VFList;

/*函数运行现场。函数运行时，需要保存变量信息，执行的位置信息等*/
class VFScene
{
};

/*函数*/
class VFunction
{
public :
  virtual void Run(VMachine *machine) = 0;

private:
  /*serail_的值在program生成时产生，每个program下的function的serial是唯一的。
    可将其看作C中的函数地址，C中每个函数的地址在某个确定的program中都是唯一的。*/
  uint4_t serial_; 
  VFList sub_functions_;
};

/*函数参数*/
class VParameter
{
};

/*
  函数返回
*/
class VReturn
{
};

/*每条sql将被转化为一个program。每个program都由若干的function组成*/
class VProgram
{
  uint32_t function_amount() const {return function_amount_;}
private:
  uint32_t  funcion_amount_; //程序中的函数个数
  VFunction *entrance_;
};

/* VProgram运行时需要一个环境。这个环境就是VMachine。
   在VMachine中，被调用函数获取到参数，调用函数获取返回值
   在VMachine中，记录调用信息，完成程序执行的控制
   通过VMachine完成编程中的一个概念，代码和数据的分离
*/
class VMachine
{
public:
  SetReturn(VReturn *vreturn);
  VReturn *GetReturn();

private:
  VProgram *program_; /*虚拟机所运行的program*/
  uint4_t scenes_amount_; /*scenes数组长度，与program的function_amount_相同*/
  VFunctionScene **scenes_; /*一个program不会有太多function，所以使用一个指针数组为每一个function保存现场环境。通过每个function的序列号（serial_）来访问*/
};

#endif //LSQL_SERVER_VM_VM_H_
