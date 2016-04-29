#ifndef LSQL_SERVER_VM_VM_H_
#define LSQL_SERVER_VM_VM_H_

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

   ？？需要callstack来记录调用堆栈和每层函数执行当前状态。调用堆栈用于函数返回时找到调用者，恢复每层函数的当前状态用于继续执行后续的操作。

*/

/*
一、关于vm
vm的概念类似cpu，vprogram可以在各个不同的vm上运行
1、每个vm对象对应一个Thread对象，也就是每创建一个vm对象则创建一个线程，该线程进行获取vprogram进行运行
2、vm对象用来代表thread的情况
二、关于vos
vm是运行资源，vos是管理这些资源。相当于操作系统，编译好的vprogram通过vos，在vm上进行运行。
1、server启动，只有一个vos对象运行
*/

using namespace std;

/*VSQL需要返回*/
class VSqlResult
{
public :
  enum Type_enum
  {
    ROWSET = 1,
    ROWCOUNT = 2,
  };
  typedef Type_enum Type;

  Type result_type() { return type_; }

protected :
  VSqlResult() {}
  Type type_;
};

class RowsetResult : public VSqlResult
{
public :
  RowsetResult()
  {
    type_ = Rowset;
  }

private :
  void *rowset_; //
};

class RowcountResult : public VSqlResult
{
public :
  RowcountResult()
  {
    type_ = Rowcount;
  }
private :
  int64_t rowcount_;
};

#endif //LSQL_SERVER_VM_VM_H_
