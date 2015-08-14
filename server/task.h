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
  TASK_PI = 1,
  TASK_RR = 2,
  TASK_PROCESS_MESSAGE
};

struct task_struct
{
  TaskType_e type;
  void       *content;
  Session    *session;
};
typedef task_struct task_t;

//用于记录task相关的信息
//使用静态变量是因为task的分配/回收和进栈/出栈调用可能比较频繁
class TaskManager
{
public :
  static lret Initialize();
  static lret Deinitialize();

  static task_t *Allocate();
  static void Free(task_t *task);

  static task_t* Dequeue();
  static void EnqueuePI(task_t *task);
  static void EnqueueRR(task_t *task);

private :
  static task_t* DequeuePI();
  static task_t* DequeueRR();

private :
  static Thread* BuildThreadsInfo(uint32_t number);
  static lret StartProcessingThreads();

private :
  static task_t task_test_;
  static int32_t task_number_;
  static lmutex_t pi_mutex_; //pi queue互斥量
  static lmutex_t rr_mutex_; //rr queue互斥量
  static lmutex_t free_mutex_t; //free链表的互斥量
  static lsemaphore_t semaphore_;  //queue semaphore
  static list<task_t*> free_tasks_;
  static bool initialized_;
  static Thread *threads_; //运行task的Thread对象

  //任务队列
  //rr的优先级高于pi
  static list<task_t*> pi_queue_; //从客户端输入的任务，pi（process input）
  static list<task_t*> rr_queue_; //返回客户结果的任务，rr（return result）
};

void
task_process(const task_t *task);


#endif //LSQL_SERVER_TASK_H_

