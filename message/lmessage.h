#ifndef LSQL_MESSAGE_LMESSAGE_H_
#define LSQL_MESSAGE_LMESSAGE_H_

#include "lsql.h"
#include "lendian.h"
#include "enet.h"
#include "lmemory.h"
#include "lvio.h"


//MSG is short for MESSAGE
//message struct
//|--------------------------------------|
//|transfer head|bussiness logic         |
//|--------------------------------------|
//|             |head      | body        |
//|--------------------------------------|



//|--------------------------------------
//|logic head
//|-------------------
//| logic id | result | statement id | row number
//|--------------------------
//transfer head:消息传送中的信息，如消息长度等，与请求处理的内容无关
//bussness logic:业务逻辑，包括两部分，逻辑头和逻辑内容
//logic head:包括诸如业务逻辑的类型（如登录验证/SQL执行等具体需要处理内容，为业务逻辑公共或大部分业务逻辑拥有的信息，或者在消息结束后需要写入的信息）
//logic body:具体类型下的详细内容，如登录验证需要将用户名/密码等信息放在该部分

//定义最大消息长度。LSQL一次性完成数据的接受和发送，不支持在通讯中多次发送数据，所以所有发送内容都将保存在内存中，以简化程序的逻辑
#define LMSG_MAX_LENGTH (16 * 1024 * 1024)

#define LMSG_TRANSFER_HEAD_SIZE 32
#define LMSG_LOGIC_HEAD_SIZE 128
#define LMSG_HEAD_SIZE (LMSG_TRANSFER_HEAD_SIZE + LMSG_LOGIC_HEAD_SIZE)

#define LMSG_TRANSFER_HEAD      0
#define LMSG_TRANSFER_LENGTH    LMSG_TRANSFER_HEAD
#define LMSG_TRANSFER_END       (LMSG_TRANSFER_LEN + sizeof(uint32_t))

#define LMSG_LOGIC_HEAD      0
#define LMSG_LOGIC_ID        LMSG_LOGIC_HEAD
#define LMSG_LOGIC_END       (LMSG_LOGIC_ID + sizeof(uint16_t))

//logic id
#define LMSG_LOGIC_ID_LOGIN 1
#define LMSG_LOGIC_ID_EXECUTION 2
#define LMSG_LOGIC_ID_PREPARE 3

/* transfer head read/write*/
/*LENGTH*/
inline uint32_t lmsg_transfer_read_length(uint8_t *msg)
{
  return lendian_read_uint32(msg + LMSG_TRANSFER_LENGTH);
}

inline void lmsg_transfer_write_length(uint8_t *msg, uint32_t length)
{
  lendian_write_uint32(msg + LMSG_TRANSFER_LENGTH, length);
}

/* logic head read/write*/
/*ID 用于标识当前需要处理的逻辑*/
inline uint16_t lmsg_read_logic_id(uint8_t *msg)
{
  return lendian_read_uint16(msg);
}

inline void lmsg_write_logic_id(uint8_t *msg, uint16_t id)
{
  lendian_write_uint16(msg, id);
}

class Vio;

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
  uint8_t *logic_body_;
  uint32_t offset_;

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

  lret Recieve(Vio *vio)
  {
    int r = vio->Recieve(buffer_, buffer_size_);

    if (r < 0)
      return LSQL_ERROR;

    if (r == 0)
    {
      transfer_length_ = 0;
      return LSQL_SUCCESS;
    }

    if (r > LMSG_MAX_LENGTH)
    {
      return LSQL_ERROR;
    }

    transfer_length_ = lmsg_transfer_read_length(transfer_head_);
    if (r > buffer_size_)
    {
      //重新分配内存空间，并接收全部数据
    }

    logic_length_ = transfer_length_ - LMSG_HEAD_SIZE;
  }

  lret Send(Vio *vio)
  {
    int r = vio->Send(buffer_, transfer_length_);
    offset_ = LMSG_TRANSFER_HEAD_SIZE;
    return LSQL_SUCCESS;
  }

  //逻辑头部分的读写
  void WriteLogicId(uint16_t id)
  {
    lendian_write_uint16(logic_head_ + LMSG_LOGIC_ID, id);
  }

  uint16_t ReadLogicId()
  {
    return lendian_read_uint16(logic_head_ + LMSG_LOGIC_ID);
  }

  //获取logic body
  uint8_t *ReadLogicBody(uint32_t *size)
  {
    *size = logic_length_ - LMSG_LOGIC_HEAD_SIZE;
    return logic_body_;
  }

  //写入数据到消息内
  lret Write(void *data, uint32_t length)
  {
    //判断是否超过最大消息长度
    if ((length + offset_) > LMSG_MAX_LENGTH)
      return LSQL_ERROR;

    offset_ += length;
    return LSQL_SUCCESS;
  }

  lret WriteUint8(uint8_t value)
  {
    if ((offset_ + sizeof(uint8_t)) > LMSG_MAX_LENGTH)
      return LSQL_ERROR;

    lendian_write_uint8(buffer_ + offset_, value);
    return LSQL_SUCCESS;
  }

  lret WriteUint16(uint16_t value)
  {
    if ((offset_ + sizeof(uint16_t)) > LMSG_MAX_LENGTH)
      return LSQL_ERROR;

    lendian_write_uint16(buffer_ + offset_, value);
    return LSQL_SUCCESS;
  }

  lret WriteUint32(uint32_t value)
  {
    if ((offset_ + sizeof(uint32_t)) > LMSG_MAX_LENGTH)
      return LSQL_ERROR;

    lendian_write_uint32(buffer_ + offset_, value);
    return LSQL_SUCCESS;
  }

  lret WriteUint64(uint64_t value)
  {
    if ((offset_ + sizeof(uint64_t)) > LMSG_MAX_LENGTH)
      return LSQL_ERROR;

    lendian_write_uint64(buffer_ + offset_, value);
    return LSQL_SUCCESS;
  }
};

#endif // LSQL_INCLUDE_LMESSAGE_H_
