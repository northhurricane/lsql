#include "lmessage_execute.h"

lret
lmessage_prepare_request_write(Message *message
                               , lmessage_execute_request_t *prepare)
{
  //logic id
  message->WriteLogicId(LMSG_LOGIC_ID_PREPARE);

  return LSQL_SUCCESS;
}

lret
lmessage_prepare_request_read(Message *message
                              , lmessage_execute_request_t *prepare)
{
  uint32_t size = 0;
  uint32_t offset = 0;
  uint8_t *buffer = message->ReadLogicBody(&size);

  return LSQL_SUCCESS;
}

