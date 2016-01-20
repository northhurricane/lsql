#include "lsql.h"
#include "lmessage_login.h"

void
lmsg_login_req_head_write()
{
  lmsg_action_head_t head;
  head.action_id = LMSG_ACTION_LOGIN;
  head.result = 0;
  head.info_num = 0;
  head.session_id = 0;
  head.stmt_id = 0;
}

lret
lmsg_login_req_write(Message *message, lmsg_login_req_t *req)
{
  uint8_t *buffer;
  uint32_t buffer_size;

  buffer_size = message->GetActBodyBuffer(&buffer_size);
  NetWriteStream stream(buffer, buffer_size);

  //TODO:填写login的信息

  uint8_t *msg;
  uint32_t msg_len;

  msg = stream.FinishWriting(&msg_len);
  message.WriteMsgBuffer(act_body, act_body_len);

  return LSQL_SUCCESS;
}

lret
lmsg_login_req_read(uint8_t *msg, uint32_t msg_len, lmsg_login_req_t *login)
{
  return LSQL_SUCCESS;
}

lret
lmsg_login_resp_write(Message *message, lmsg_login_resp_t *resp)
{
  return LSQL_SUCCESS;
}

lret
lmsg_login_resp_read(
  uint8_t *msg, uint32_t msg_len, lmsg_login_resp_t *resp)
{
  return LSQL_SUCCESS;
}

