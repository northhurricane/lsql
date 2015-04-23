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

/*每条sql将被转化为一个program。每个program都由若干的function组成*/
class VProgram
{
public :
  void Run(VProcess *process);

  uint32_t function_amount() {return function_amount_;}
  bool Link(VFunction *entrance);
  VFunction *entrance() { return entrance_; }
  VProgram();

private :
  uint32_t  function_amount_; //程序中的函数个数
  VFunction *entrance_;

  bool GenerateFunctionSerial(VFunction *function);

};

/* VProgram运行时需要一个环境。这个环境就是VProcess。
   通过VProcess完成一个事情，模拟进程，具备操作系统中进程的特性。
   从而达到代码和运行时数据的分离。VProgram对应代码，VProcess对应运行数据。

   Todo : 虚拟进程的信息可以分类，各函数的数据空间，进程的运行状态
*/
class VProcess
{
public:
  void Run(); //相当于代码运行
  void Initialize(VProgram *program); //相当于代码载入
  void Deinitialize(); //相当于代码退出，清理环境

  VFScene *GetScene(uint32_t serial)
  {
    lassert(serial < scenes_amount_);

    return scenes_[serial];
  }

  Memory *memory() { return memory_; }
  uint16_t rows_array_size() { return rows_array_size_; }

private:
  VProgram *program_; /*虚拟机所运行的program*/
  AutoHeap *memory_; /*运行中所使用的内存，在进程结束后统一释放*/
  uint32_t scenes_amount_; /*scenes数组长度，与program的function_amount_相同*/
  VFScene **scenes_; /*一个program不会有太多function，所以使用一个指针数组为每一个function保存现场环境。通过每个function的序列号（serial_）来访问*/

  uint16_t rows_array_size_; /* 该进程中VFData中行数组的大小 */

  bool InitializeFunctionScene(VFunction *function);
};

#endif //LSQL_SERVER_VM_VM_H_
