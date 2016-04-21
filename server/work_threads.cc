#include "work_threads.h"
#include "LThread.h"

/*连接处理线程*/
lret work_thread_create_deal_connect()
{
  
  return LSQL_SUCCESS;
}

/*断开处理线程*/
lret work_thread_create_deal_disconnect()
{
  return LSQL_SUCCESS;
}

/*消息处理线程*/
lret work_thread_create_deal_message()
{
  return LSQL_SUCCESS;
}


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


