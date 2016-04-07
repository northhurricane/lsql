#include "lmessage_execute.h"

lret
lmsg_execute_req_write(Message *message, lmsg_execute_req_t *req)
{
  //logic id
  //message->WriteLogicId(LMSG_LOGIC_ID_PREPARE);

  return LSQL_SUCCESS;
}

lret
lmsg_execute_req_read(Message *message, lmsg_execute_req_t *req)
{
  uint32_t size = 0;
  uint32_t offset = 0;
  //  uint8_t *buffer = message->ReadLogicBody(&size);

  return LSQL_SUCCESS;
}

