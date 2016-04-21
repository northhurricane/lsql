#include "work_threads.h"
#include "LThread.h"

/*连接处理线程*/
int work_thread_deal_connect(LThread *thread)
{
  LThreadManager::GetInstance()->Add(thread);
  while (true)
  {
    //处理连接事件
  }
  LThreadManager::GetInstance()->Remove(thread);
  LThread::Destroy(thread);

  return 0;
}

const char *THREAD_DEAL_CONNECT = "THREAD_DEAL_CONNECT";

lret work_thread_create_deal_connect()
{
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


