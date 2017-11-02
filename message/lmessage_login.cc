#include "lsql.h"
#include "lmessage_login.h"

void
lmsg_login_req_head_write()
{
  lmsg_action_head_t head;
  head.action_id = LMSG_ACTION_LOGIN;
  head.result = 0;
  head.session_id = 0;
  head.stmt_id = 0;
}

lret
lmsg_login_req_write(Message *message, lmsg_login_req_t *req)
{
  return LSQL_SUCCESS;
}

lret
lmsg_login_req_read(Message *message, lmsg_login_req_t *login)
{
  return LSQL_SUCCESS;
}

lret
lmsg_login_resp_write(Message *message, lmsg_login_resp_t *resp)
{
  return LSQL_SUCCESS;
}

lret
lmsg_login_resp_read(Message *message, lmsg_login_resp_t *resp)
{
  return LSQL_SUCCESS;
}

