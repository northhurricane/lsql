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
  TASK_NONE = 0,
  TASK_PROCESS_MESSAGE
};

struct task_struct
{
public :
  TaskType_e type;
  void       *content;
  Session    *session;
};
typedef task_struct task_t;

//用于记录task相关的信息
//使用静态变量是因为task的分配/回收和进栈/出栈调用可能比较频繁
class TaskManager
{
private :
  static task_t task_test_;
  static int32_t task_number_;
  static lmutex_t mutex_;
  static lsemaphore_t semaphore_;  //queue semaphore
  static list<task_t*> queue_;
  static list<task_t*> free_tasks_;
  static bool initialized_;
  static Thread *threads_; //运行task的Thread对象

public :
  static lret Initialize();
  static lret Deinitialize();

  static task_t *Allocate();
  static void Free(task_t *task);

  static void Enqueue(task_t *task);
  static task_t* Dequeue();

private :
  static Thread* BuildThreadsInfo(uint32_t number);
  static lret StartProcessingThreads();
};

void
task_process(const task_t *task);


#endif //LSQL_SERVER_TASK_H_

