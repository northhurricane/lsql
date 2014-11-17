#include "lsql.h"
#include "lmessage_login.h"


lret
lmessage_login_request_write(Message *message, lmessage_login_request_t *login)
{
  //logic id
  message->WriteLogicId(LMSG_LOGIC_ID_LOGIN);

  message->WriteUint32(login->version);

  message->WriteUint32(login->user_length);
  message->Write(login->user, login->user_length);

  message->WriteUint32(login->password_length);
  message->Write(login->password, login->password_length);

  return LSQL_SUCCESS;
}

lret
lmessage_login_request_read(Message *message, lmessage_login_request_t *login)
{
  uint32_t size = 0;
  uint32_t offset = 0;
  uint8_t *buffer = message->ReadLogicBody(&size);

  login->version = lendian_read_uint32(buffer + offset);
  offset += sizeof(uint32_t);

  login->user_length = lendian_read_uint32(buffer + offset);
  offset += sizeof(uint32_t);
  login->user = buffer + offset;
  offset += login->user_length;

  login->password_length = lendian_read_uint32(buffer + offset);
  offset += sizeof(uint32_t);
  login->password = buffer + offset;
  offset += login->password_length;

  lassert(offset == size);

  return LSQL_SUCCESS;
}


