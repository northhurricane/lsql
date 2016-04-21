#include <list>
#include "work_threads.h"
#include "LThread.h"
#include "lmutex.h"
#include "lsemaphore.h"

using namespace std;

/*连接处理线程*/
list<LPort*> connect_task_list;
lmutex_t connect_task_mutex;
lsemaphore_t connect_task_sem;

void connect_task_enqueue(LPort *port)
{
  lmutex_lock(&connect_task_mutex);
  connect_task_list.push_back(port);
  lmutex_unlock(&connect_task_mutex);

  lsemaphore_post(&connect_task_sem);
}

LPort* connect_task_dequeue()
{
  LPort *port;

  lsemaphore_wait(&connect_task_sem);

  lmutex_lock(&connect_task_mutex);
  port = connect_task_list.front();
  connect_task_list.pop_front();
  lmutex_unlock(&connect_task_mutex);

  return port;
}

int work_thread_deal_connect(LThread *thread)
{
  LThreadManager::GetInstance()->Add(thread);
  LPort *port;
  while (true)
  {
    //处理连接事件
    port = connect_task_dequeue();

    //判断线程状态
    if (thread->stop_thread())
    {
    }
  }

  //清理线程上使用的资源
  //清理connect_task_list上的端口
  //清理在LThreadManager
  LThreadManager::GetInstance()->Remove(thread);
  //删除线程对象
  LThread::Destroy(thread);
  //清除同步控制
  lmutex_destroy(&connect_task_mutex);
  lsemaphore_destroy(&connect_task_sem);

  return 0;
}

const char *THREAD_DEAL_CONNECT = "THREAD_DEAL_CONNECT";

lret work_thread_create_deal_connect()
{
  lmutex_init(&connect_task_mutex);
  lsemaphore_init(&connect_task_sem, 0);

  LThread *thread = LThread::Create(THREAD_DEAL_CONNECT);

  //初始化thread的信息

  //创建线程
  lsqld_thread_create(thread);

  return LSQL_SUCCESS;
}

/*断开处理线程*/
int work_thread_deal_disconnect(LThread *thread)
{
  LThreadManager::GetInstance()->Add(thread);
  while (true)
  {
    //处理断开事件
  }
  LThreadManager::GetInstance()->Remove(thread);
  LThread::Destroy(thread);

  return 0;
}

const char *THREAD_DEAL_DISCONNECT = "THREAD_DEAL_DISCONNECT";

lret work_thread_create_deal_disconnect()
{
  LThread *thread = LThread::Create(THREAD_DEAL_CONNECT);

  //初始化thread的信息

  //创建线程
  lsqld_thread_create(thread);

  return LSQL_SUCCESS;
}

/*消息处理线程*/
int work_thread_deal_message(LThread *thread)
{
  LThreadManager::GetInstance()->Add(thread);
  while (true)
  {
    //处理断开事件
  }
  LThreadManager::GetInstance()->Remove(thread);
  LThread::Destroy(thread);

  return 0;
}

const char *THREAD_DEAL_MESSAGE = "THREAD_DEAL_MESSAGE";

lret work_thread_create_deal_message()
{
  LThread *thread = LThread::Create(THREAD_DEAL_CONNECT);

  //初始化thread的信息

  //创建线程
  lsqld_thread_create(thread);

  return LSQL_SUCCESS;
}

/*初始化及销毁*/
lret
work_threads_init()
{
  work_thread_create_deal_connect();
  work_thread_create_deal_disconnect();
  work_thread_create_deal_message();

  return LSQL_SUCCESS;
}

lret
work_threads_deinit()
{
  return LSQL_SUCCESS;
}


