#ifndef LSQL_MESSAGE_LMESSAGE_LOGIN_H_
#define LSQL_MESSAGE_LMESSAGE_LOGIN_H_

#include "lmessage.h"

//登录请求信息
struct lmsg_login_req_struct
{
  uint8_t *user;
  uint32_t user_length;
  uint8_t *password;
  uint32_t password_length;
};
typedef lmsg_login_req_struct lmsg_login_req_t;

//登录返回信息
struct lmsg_login_resp_struct
{
  uint32_t version;
};
typedef lmsg_login_resp_struct lmsg_login_resp_t;

lret
lmsg_login_req_write(Message *message, lmsg_login_req_t *req);

lret
lmsg_login_request_read(Message *message, lmsg_login_req_t *req);

lret
lmsg_login_resp_write(Message *message, lmsg_login_resp_t *resp);

lret
lmsg_login_resp_read(Message *message, lmsg_login_resp_t *resp);

#endif //LSQL_MESSAGE_LMESSAGE_LOGIN_H_
