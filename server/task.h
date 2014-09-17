#ifndef _TASK_H
#define _TASK_H

#include "conn.h"

enum TASK_TYPE
{
};

class TASK
{
public :
  static TASK *alloc();
  static void free(TASK *task);
  static void enqueue(TASK *task);
  static TASK *dequeue();

public :
  bool canceled;  //set this flag to cancel all the work
  TASK_TYPE type;
  void *task_content;
};

void task_connection_build(TASK *task, enet_socket_t socket);

#endif //_TASK_Hb

