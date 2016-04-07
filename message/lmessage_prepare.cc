#include "lmessage_prepare.h"

lret
lmsg_prepare_req_write(Message *message, lmsg_prepare_req_t *prepare)
{
  //logic id
  //message->WriteLogicId(LMSG_LOGIC_ID_PREPARE);

  return LSQL_SUCCESS;
}

lret
lmsg_prepare_req_read(Message *message, lmsg_prepare_req_t *prepare)
{
  uint32_t size = 0;
  uint32_t offset = 0;
  //uint8_t *buffer = message->ReadLogicBody(&size);

  return LSQL_SUCCESS;
}

