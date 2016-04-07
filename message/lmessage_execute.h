#ifndef LSQL_MESSAGE_LMESSAGE_EXECUTE_H_
#define LSQL_MESSAGE_LMESSAGE_EXECUTE_H_

#include "lmessage.h"

struct lmsg_execute_req_struct
{
  bool exec_direct; //是否直接执行
  char *sql; //exec_direct为true时，该变量指向执行的语句的sql
  uint32_t sql_lenght; //sql语句的长度
};
typedef struct lmsg_execute_req_struct lmsg_execute_req_t;

lret
lmsg_execute_req_write(Message *message, lmsg_execute_req_t *prepare);

lret
lmsg_execute_req_read(Message *message, lmsg_execute_req_t *prepare);


#endif //LSQL_MESSAGE_LMESSAGE_EXECUTE_H_

