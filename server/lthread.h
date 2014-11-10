#ifndef _LTHREAD_H
#define _LTHREAD_H

#include "thread.h"
#include "mutex.h"
#include <list>

using namespace std;

#define OP_INFO_BUFFER_SIZE 256

//参考mysql的概念，该对象代表服务器端线程，每创建一个服务器端的线程，就要生成一个LTHREAD对象，线程退出时将删除该变量
class LTHREAD
{
public :
  thread_t thread;  //操作系统下thread的

  thread_function func; //线程函数
  void *para;  //线程参数
  char op_info_buffer[OP_INFO_BUFFER_SIZE];  //当前线程操作内容
};

class LTHREAD_MANAGER
{
public :
  list<LTHREAD*> threads; //用于记录server正在运行中的线程
  mutex_t mutex; //

  void add(LTHREAD *thread)
  {
    thread_lock(&mutex);
    threads.add(thread);
    thread_unclock(&mutex);
  }

  void remove(LTHREAD *thread)
  {
    thread_lock(&mutex);
    threads.push_back(thread);
    thread_unlock(&mutex);
  }
};


lret
lthread_create(LTHREAD *lthread);

#endif //_LTHREAD_H
