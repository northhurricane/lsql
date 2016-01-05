#ifndef LSQL_VPROCESS_H_
#define LSQL_VPROCESS_H_

#include <list>
/* 
VProgram运行时需要一个环境。这个环境就是VProcess。
通过VProcess完成一个事情，模拟进程，具备操作系统中进程的特性。
从而达到代码和运行时数据的分离。VProgram对应代码，VProcess对应运行数据。

从服务器的对象来说，语句对象也虚拟进程的是1对1的关系。每个语句对象只能有至多一个虚拟进程在运行。

VProcess记录的信息
1、VFunction调用堆栈
2、各个VFunction的运行环境

*/

class VFunction;
class VProgram;

using namespace std;

class VProcess
{
public:
  void Start(); //相当于代码运行
  void Initialize(VProgram *program); //相当于代码载入
  void Deinitialize(); //相当于代码退出，清理环境

  VFScene *GetScene(uint32_t serial)
  {
    lassert(serial < scenes_amount_);

    return scenes_[serial];
  }

  Memory *memory() { return memory_; }
  uint16_t rows_array_size() { return rows_array_size_; }

  void CallFunc();

private:
  VProgram *program_; /*虚拟机所运行的program*/
  AutoHeap *memory_; /*运行中所使用的内存，在进程结束后统一释放*/
  VFScene **scenes_; /*一个program不会有太多function，所以使用一个指针数组为每一个function保存现场环境。通过每个function的序列号（serial_）来访问*/
  uint16_t rows_array_size_; /* 该进程中VFData中行数组的大小 */

  //运行时信息
  //函数调用堆栈
  list<VFunction*> stack;
  //当前执行函数
  VFunction *current_func_;
  //初始化各个函数的运行环境
  bool InitializeFunctionScene(VFunction *function);
};

#endif //LSQL_VPROCESS_H_
