#ifndef LSQL_MESSAGE_LMESSAGE_PREPARE_H_
#define LSQL_MESSAGE_LMESSAGE_PREPARE_H_

#include "lmessage.h"

struct lmessage_prepare_request_struct
{
  uint8_t *sql_text;
  uint32_t length;
};
typedef struct lmessage_prepare_request_struct lmessage_prepare_request_t;

struct lmessage_prepare_response_struct
{
  uint32_t type;  //statement type. such as insert/select/delete/update/create table etc.
};
typedef struct lmessage_prepare_response_struct lmessage_prepare_response_t;

lret
lmessage_prepare_request_write(Message *message, lmessage_prepare_request_t *prepare);

lret
lmessage_prepare_request_read(Message *message, lmessage_prepare_request_t *prepare);


#endif //LSQL_MESSAGE_LMESSAGE_PREPARE_H_
