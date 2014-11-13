#ifndef LSQL_SERVER_LSQLD_THREAD_H
#define LSQL_SERVER_LSQLD_THREAD_H

#include "lsql.h"
#include "lthread.h"
#include "lmutex.h"
#include <list>

using namespace std;

#define OP_INFO_BUFFER_SIZE 256
#define THREAD_INFO_BUFFER_SIZE 64

//参考mysql的概念，该对象代表服务器端线程，每创建一个服务器端的线程，就要生成一个LTHREAD对象，线程退出时将删除该变量
class Thread
{
private :
  lthread_t thread_;  //lsql封装的操作系统下thread标识

  lthread_function_t func_; //线程函数
  void *para_;  //线程参数
  char op_info_buffer_[OP_INFO_BUFFER_SIZE];  //当前线程操作内容
  char thread_info_buffer_[THREAD_INFO_BUFFER_SIZE]; //该线程的初始化信息

public :
  Thread();
  Thread(lthread_function_t function, void *para, char *thread_info);

  lthread_function_t func() {return func_;}
  void set_func(lthread_function_t func) { func_ = func; }
  void *para() {return para_;}
  void set_para(void * para) { para_ = para; }
  const char *thread_info() {return thread_info_buffer_; }
  void set_thread_info(const char *thread_info) {}
  const char *op_info() { return op_info_buffer_; }
  void set_op_info(const char *op_info) {}
  lthread_t *thread() {return &thread_;}
};

//用于记录服务器中的工作线程
class ThreadManager
{
private :
  list<Thread*> threads_; //用于记录server正在运行中的线程
  lmutex_t mutex_; //

  static ThreadManager *instance_;
  ThreadManager();

public :
  void Add(Thread *thread)
  {
    lmutex_lock(&mutex_);
    threads_.push_back(thread);
    lmutex_unlock(&mutex_);
  }

  void Remove(Thread *thread)
  {
    lmutex_lock(&mutex_);
    threads_.remove(thread);
    lmutex_unlock(&mutex_);
  }

  static lret Initialize();
  static lret Deinitialize();

  static inline ThreadManager *GetInstance()
  {
    lassert(instance_ != NULL);

    return instance_;
  }
};

lret
lsqld_thread_create(Thread *thread);

#endif //LSQL_SERVER_LSQLD_THREAD_H
