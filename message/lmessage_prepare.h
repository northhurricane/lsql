#ifndef LSQL_MESSAGE_LMESSAGE_PREPARE_H_
#define LSQL_MESSAGE_LMESSAGE_PREPARE_H_

#include "lmessage.h"

struct lmsg_prepare_req_struct
{
  uint8_t *sql_text;
  uint32_t length;
};
typedef struct lmsg_prepare_req_struct lmsg_prepare_req_t;

struct lmsg_prepare_resp_struct
{
  uint32_t type;  //statement type. such as insert/select/delete/update/create table etc.
};
typedef struct lmsg_prepare_resp_struct lmsg_prepare_resp_t;

lret
lmsg_prepare_req_write(Message *message, lmsg_prepare_req_t *req);

lret
lmsg_prepare_req_read(Message *message, lmsg_prepare_req_t *req);


#endif //LSQL_MESSAGE_LMESSAGE_PREPARE_H_
