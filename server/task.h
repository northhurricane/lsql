#ifndef LSQL_SERVER_TASK_H_
#define LSQL_SERVER_TASK_H_

#include <list>
#include "lsql.h"
#include "lmutex.h"
#include "lsemaphore.h"

using namespace std;

class Session;
class Thread;

enum TaskType_e
{
  TASK_NONE = 0
};

class Task
{
public :
  TaskType_e type;
  void       *content;
  Session    *session;
};

//用于记录task相关的信息
//使用静态变量是因为task的分配/回收和进栈/出栈调用可能比较频繁
class TaskManager
{
private :
  static int32_t task_number_;
  static lmutex_t mutex_;
  static lsemaphore_t semaphore_;  //queue semaphore
  static list<Task*> queue_;
  static list<Task*> free_tasks_;
  static bool initialized_;
  static Thread *threads_; //运行task的Thread对象

public :
  static lret Initialize();
  static lret Deinitialize();

  static Task *Allocate();
  static void Free(Task *task);

  static void Enqueue(Task *task);
  static Task* Dequeue();

private :
  static Thread* BuildThreadsInfo(uint32_t number);
  static lret StartProcessingThreads();
};

#endif //LSQL_SERVER_TASK_H_

