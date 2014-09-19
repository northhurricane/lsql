#ifndef _TASK_H
#define _TASK_H

#include "conn.h"
#include "lsem.h"
#include "lmutex.h"

class CONNECTION;

enum TASK_TYPE
{
  TASK_NONE = 0,
  //net operation
  TASK_CONNECTION,  //connection
  TASK_REQUEST,     //message request from client
  TASK_RESPONSE,    //message response to client

};

class TASK
{
public :
  static TASK *allocate();
  static void free(TASK *task);
  static void enqueue(TASK *task);
  static TASK *dequeue();

public :
  bool       canceled;  //set this flag to cancel all the work
  TASK_TYPE  type;
  void       *task_content;
  CONNECTION *connection;  //the connection belong to

private:
  static lsem_t  task_queue_sem;    //for 
  static lmutex_t task_queue_mutex; 
  
};

void task_execute(TASK *task);

#endif //_TASK_Hb

