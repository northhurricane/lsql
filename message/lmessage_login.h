#ifndef LSQL_MESSAGE_LMESSAGE_LOGIN_H_
#define LSQL_MESSAGE_LMESSAGE_LOGIN_H_

#include "lmessage.h"

struct lmessage_login_request_struct
{
  uint32_t version;
  uint8_t *user;
  uint32_t user_length;
  uint8_t *password;
  uint32_t password_length;
};
typedef lmessage_login_request_struct lmessage_login_request_t;

struct lmessage_login_response_struct
{
  uint32_t version;
};
typedef lmessage_login_response_struct lmessage_login_response_t;

lret
lmessage_login_request_write(Message *message, lmessage_login_request_t *login);

lret
lmessage_login_request_read(Message *message, lmessage_login_request_t *login);


#endif //LSQL_MESSAGE_LMESSAGE_LOGIN_H_
