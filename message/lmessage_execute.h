#ifndef LSQL_MESSAGE_LMESSAGE_EXECUTE_H_
#define LSQL_MESSAGE_LMESSAGE_EXECUTE_H_

#include "lmessage.h"

struct lmessage_execute_request_struct lmessage_execute_request_struct
{
  bool exec_direct; //是否直接执行
  char *sql; //exec_direct为true时，该变量指向执行的语句的sql
  uint32_t sql_lenght; //sql语句的长度
};
typedef struct lmessage_execute_request_struct lmessage_execute_request_t;

lret
lmessage_execute_request_write(Message *message
                               , lmessage_prepare_request_t *prepare);

lret
lmessage_execute_request_read(Message *message
                              , lmessage_prepare_request_t *prepare);


#endif //LSQL_MESSAGE_LMESSAGE_EXECUTE_H_

