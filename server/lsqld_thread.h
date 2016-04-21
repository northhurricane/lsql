#ifndef LSQL_SERVER_LSQLD_THREAD_H
#define LSQL_SERVER_LSQLD_THREAD_H

#include "lsql.h"
#include "lthread.h"
#include "lmutex.h"
#include <list>
#include <string.h>

/*
参考mysql的概念，该对象代表服务器端线程，每创建一个服务器端的线程，就要生成一个LTHREAD对象，线程退出时将删除该变量。
服务器端的线程模型是这样的的
1、服务器端所有的线程线程创建，都调用封装好的函数lsqld_thread_create
2、Thread对象将作为参数，传递给线程函数
3、所有的线程函数必须将Thread对象作为参数。2和3形成2级参数机制，也就是线程函数通过一级参数Thread对象来获得自己真正需要的参数，也就是通过Thread对象的pare函数，获取线程函数的特有参数。
4、所有的线程函数通过检查Thread对象的停止设置，进行退出操作。（退出的设置由创建线程的模块完成，该论述属于完美假设。大多数代码中，模块的划分和使用都达不到完美）
*/

using namespace std;

#define OP_INFO_BUFFER_SIZE 256
#define THREAD_INFO_BUFFER_SIZE 64

class LThread;
typedef int (*lsqld_thread_func_t)(LThread *thread);

class LThread
{
private :
  lthread_t thread_;  //lsql封装的操作系统下thread标识，在线程创建后有效

  //线程初始信息，运行过程中不会改变
  lsqld_thread_func_t func_; //线程函数
  void *para_;  //线程的实际参数
  char thread_info_buffer_[THREAD_INFO_BUFFER_SIZE]; //该线程的初始化信息

  //运行时信息，会发生改变
  char op_info_buffer_[OP_INFO_BUFFER_SIZE];  //当前线程操作内容
  bool stop_thread_; //初始化为false，需要退出时进行设置，通知thread进行退出

public :
  LThread();
  //LThread(lsqld_lthread_func_t function, void *para, char *thread_info);

  lthread_t *thread() { return &thread_; }
  void set_thread(lthread_t thread) { thread_ = thread; }

  lsqld_thread_func_t func() { return func_; }
  void *para() {return para_;}
  const char *thread_info() {return thread_info_buffer_; }

  const char *op_info() { return op_info_buffer_; }
  void set_op_info(const char *op_info)
  {
    //拷贝信息
    bool no_set_for_fast = true;
    if (no_set_for_fast)
      return ;

    //Todo : 上锁。
    strncpy(op_info_buffer_, op_info, OP_INFO_BUFFER_SIZE);
  }


  void set_stop_thread() { stop_thread_ = false; }
  bool stop_thread() { return stop_thread_; }
};

//用于记录服务器中的工作线程
class LThreadManager
{
private :
  list<LThread*> threads_; //用于记录server正在运行中的线程
  lmutex_t mutex_; //

  static LThreadManager *instance_;
  LThreadManager();

public :
  void Add(LThread *thread)
  {
    lmutex_lock(&mutex_);
    threads_.push_back(thread);
    lmutex_unlock(&mutex_);
  }

  void Remove(LThread *thread)
  {
    lmutex_lock(&mutex_);
    threads_.remove(thread);
    lmutex_unlock(&mutex_);
  }

  static lret Initialize();
  static lret Deinitialize();

  static inline LThreadManager *GetInstance()
  {
    lassert(instance_ != NULL);

    return instance_;
  }
};

/*线程初始化*/
lret
lsqld_thread_init();

/*线程销毁*/
lret
lsqld_thread_deinit();

/*创建线程*/
lret
lsqld_thread_create(LThread *thread);

/*获取当前线程的线程对象*/
LThread*
lsqld_thread_current();

/*设置当前线程的线程对象*/
void
lsqld_thread_set_current(LThread *thread);

#endif //LSQL_SERVER_LSQLD_THREAD_H
