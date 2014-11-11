#ifndef _LMESSAGE_H
#define _LMESSAGE_H

#include "lsql.h"
#include "lendian.h"
#include "enet.h"

#define LMESSAGE_HEAD_SIZE 128
#define LMESSAGE_COMMON_HEAD_SIZE 16

#define LMESSAGE_HEAD      0
#define LMESSAGE_LENGTH    LMESSAGE_HEAD
#define LMESSAGE_COMMAND   (LMESSAGE_LENGTH + sizeof(uint32_t))

//execute command
#define LMSG_REQ_EXEC LMSG_COMMON_HEAD_SIZE

inline uint32_t lmessage_read_length(uint8_t *message)
{
  return lendian_read_uint32(message + LMESSAGE_LENGTH);
}

inline void lmessage_write_length(uint8_t *message, uint32_t length)
{
  lendian_write_uint32(message + LMESSAGE_LENGTH, length);
}

inline uint16_t lmessage_read_command(uint8_t *message)
{
  return lendian_read_uint16(message);
}

inline void lmessage_write_command(uint8_t *message, uint16_t command)
{
  lendian_write_uint16(message, command);
}

class Connection;

#define LMESSAGE_BUFFER_SIZE 1024
class Message
{
public :
  uint32_t total_length;  //total message length include message head
  uint32_t body_length;   //only message length
  uint8_t head[LMESSAGE_HEAD_SIZE];
  uint8_t buffer_fast[LMESSAGE_BUFFER_SIZE];
  uint8_t *buffer;

  /*  lret begin(CONNECTION connection)
  {
    this->connection = connection;
    int r = enet_socket_read(connection->socket, head, sizeof(head), 0);

    buffer = buffer_fast;

    if (r < 0)
      return LSQL_ERROR;
    if (r == 0)
    {
      total_length = 0;
      return LSQL_SUCCESS;
    }
    total_length = lmessage_read_length(head);
    body_length = total_length - LMESSAGE_HEAD_SIZE;
  }

  void end()
  {
    if (buffer != buffer_fast)
      free(buffer);
    connection = NULL;
  }

  int read(uint8_t *buffer, uint32_t size)
  {
    return enet_socket_read(connection->socket, buffer, size, 0);
    }*/
};

#endif //_LMESSAGE_H
