#ifndef LSQL_SERVER_VM_VM_H_
#define LSQL_SERVER_VM_VM_H_

#include <list>
#include "column.h"
#include "memory.h"
#include "vfdata.h"
#include "autoheap.h"


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

class VProcess;

struct vfreturn_struct
{
  bool error; //调用是否出错
  bool over;  //函数是否结束。true表示函数执行结束，不再返回数据；false表示data成员变量中包含数据。

  VFData *data; //返回的数据
};
typedef struct vfreturn_struct vfreturn_t;

inline vfreturn_t over_return()
{
  vfreturn_t ret;
  ret.error = false;
  ret.over = true;
  ret.data = NULL;
}

/*函数运行现场。函数运行时，需要保存变量信息，执行的位置信息等*/
class VFScene
{
public :
  VFData *data() { return data_; }
  void set_data(VFData *data) { data_ = data; }
  bool over() { return over_; }
  void set_over(bool over) { over_ = over; }
  bool first_over() { return first_over_; }
  void set_first_over(bool over) { first_over_ = over; }
  bool second_over() { return second_over_; }
  void set_second_over(bool over) { second_over_ = over; }

protected :
  VFData  *data_;      //在函数执行时填写数据的地方，和VF的coldef一致

  bool over_;          //该函数是否取完数据。true表示所有数据都已经返回，false表示还可以继续返回数据
  bool first_over_;    //第一函数是否结束
  bool second_over_;   //第二函数是否结束
};

/*函数*/
class VFunction
{
public :
  //函数运行
  virtual vfreturn_t Run(VProcess *process) = 0;

  //创建函数运行时所需的运行现场，在虚拟进程的函数运行前，被调用
  virtual VFScene *CreateScene(VProcess *process) = 0;

  //销毁函数运行时所需的运行现场，在虚拟进程结束时，进行销毁
  virtual void DestroyScene(VProcess *process) = 0;
  VFunction() ;

private:
  /*serail_的值在program生成时产生，每个program下的function的serial是唯一的。
    可将其看作C中的函数地址，C中每个函数的地址在某个确定的program中都是唯一的。*/
  uint32_t serial_; 
  VFunction *first_;   //第一个被执行
  VFunction *second_;  //第二个被执行
  coldef_array_t *coldefs_; //函数返回行集的元信息
  //用于定义如何使用first_/second_的行集的信息。也就是从子函数的行集到当前函数的行集的转化。比如abs(f1), cos(f1)，f1+f2这样的计算列，或者直接将行集的某些列的数据拷贝到当前行集

public :
  VFunction *first() { return first_; }
  void set_first(VFunction *first) { first_ = first; }
  VFunction *second() { return second_; }
  void set_second(VFunction *second) { second_ = second; }
  uint32_t serial() { return serial_; }
  void set_serial(uint32_t serial) { serial_ = serial; }
  coldef_array_t *coldefs() { return coldefs_; }
};

/*VSQL需要返回*/
class VSqlResult
{
public :
  enum Type_enum
  {
    Rowset = 1,
    Rowcount = 2,
    Empty = 3
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

class EmptyResult : public VSqlResult
{
public :
  EmptyResult()
  {
    type_ = Empty;
  }
};

/*
完成如下功能：
1、初始化vm系统。如vm的运行线程等
2、进行虚拟机程序执行的调度。
3、
*/
class VMManager
{
public :
  static void RunProgram();
  
};

#endif //LSQL_SERVER_VM_VM_H_
