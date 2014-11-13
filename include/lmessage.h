#ifndef LSQL_INCLUDE_LMESSAGE_H_
#define LSQL_INCLUDE_LMESSAGE_H_

#include "lsql.h"
#include "lendian.h"
#include "enet.h"
#include "lmemory.h"

//MSG is short for MESSAGE
//message struct
//|---------------------------------------
//|transfer head|bussiness logic         |
//|--------------------------------------|
//|             |head      | content     |
//|---------------------------------------
//transfer head:消息传送中的信息，如消息长度等，与请求处理的内容无关
//bussness logic:业务逻辑，包括两部分，逻辑头和逻辑内容
//logic head:包括诸如业务逻辑的类型（如登录验证/SQL执行等具体需要处理内容，为业务逻辑公共或大部分拥有的信息）
//logic content:具体类型下的详细内容，如登录验证需要将用户名/密码等信息放在该部分

#define LMSG_TRANSFER_HEAD_SIZE 32
#define LMSG_LOGIC_HEAD_SIZE 128
#define LMSG_HEAD_SIZE (LMSG_TRANSFER_HEAD_SIZE + LMSG_LOGIC_HEAD_SIZE)

#define LMSG_TRANSFER_HEAD      0
#define LMSG_TRANSFER_LENGTH    LMSG_TRANSFER_HEAD
#define LMSG_TRANSFER_END       (LMSG_TRANSFER_LEN + sizeof(uint32_t))

#define LMSG_LOGIC_HEAD      0
#define LMSG_LOGIC_TYPE      LMSG_LOGIC_HEAD
#define LMSG_LOGIC_END       (LMSG_LOGIC_TYPE + sizeof(uint16_t))

//execute command
#define LMSG_LOGIC_LOGIN 1
#define LMSG_LOGIC_EXECUTION 2
#define LMSG_LOGIC_PREPARE 3

inline uint32_t lmessage_read_length(uint8_t *message)
{
  return lendian_read_uint32(message + LMSG_TRANSFER_LENGTH);
}

inline void lmessage_write_length(uint8_t *message, uint32_t length)
{
  lendian_write_uint32(message + LMSG_TRANSFER_LENGTH, length);
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

#define LMSG_BUFFER_SIZE (1024 * 16)
class Message
{
private :
  uint32_t transfer_length_;  //total message length recieved
  uint32_t logic_length_;   //bussiness logic part length
  uint8_t buffer_fast_[LMSG_BUFFER_SIZE];
  uint8_t *buffer_;
  uint32_t buffer_size_;
  uint8_t *transfer_head_;
  uint8_t *logic_head_;

  void SetBuffer(uint8_t *buffer, uint32_t buffer_size)
  {
    buffer_ = buffer;
    buffer_size_ = buffer_size;
    transfer_head_ = buffer;
    logic_head_ = buffer + LMSG_TRANSFER_HEAD_SIZE;
  }

public :
  Message()
  {
    SetBuffer(buffer_fast_, LMSG_BUFFER_SIZE);
  }

  ~Message()
  {
    if (buffer_fast_ != buffer_)
      lfree(buffer_);
  }

  lret Recieve(Connection *connection)
  {
    int r = enet_socket_recv(connection->socket(), buffer_, buffer_size_, 0);

    if (r < 0)
      return LSQL_ERROR;
    if (r == 0)
    {
      transfer_length_ = 0;
      return LSQL_SUCCESS;
    }
    transfer_length_ = lmessage_read_length(transfer_head_);
    logic_length_ = transfer_length_ - LMSG_HEAD_SIZE;
  }

};

#endif // LSQL_INCLUDE_LMESSAGE_H_
