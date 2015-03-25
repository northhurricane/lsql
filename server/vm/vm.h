#ifndef LSQL_SERVER_VM_VM_H_
#define LSQL_SERVER_VM_VM_H_

/* 
设计目标
每一个SQL语句的完成都是有一些列函数调用完成的。
sql的执行就变成函数的执行
sql的优化就变成函数的优化。
功能的增加就变成函数的编写。
目标是使优化变得更易读/易写/易优化

函数式语言lisp是通过函数的嵌套完成功能的开发。其优雅的形式产生这个设计思路。
(functionA argument_functionA argument_functionB)lisp的调用方式
在functionA完成之前，argument_functionA/B必须执行完成
所以，控制就变为函数的调用和结果保存，然后当前函数的执行

执行的控制变为函数调用的控制。调用函数，函数返回，传入参数，返回结果
每个函数只关注传入的参数/被调用函数的返回和自身的逻辑
*/

/*函数*/
class VFunction
{
public :
  virtual void Run(VMachine *machine) = 0;
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
private:
  VFunction *entrance_;
};



/**/
class VFunctionStack
{
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

};

#endif //LSQL_SERVER_VM_VM_H_
