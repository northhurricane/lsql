#ifndef LSQL_MESSAGE_LMESSAGE_H_
#define LSQL_MESSAGE_LMESSAGE_H_

#include "lsql.h"
#include "lendian.h"
#include "enet.h"
#include "lmemory.h"
#include "ltypedef.h"


//MSG is short for MESSAGE
//message struct
//|--------------------------------------|
//|transfer head|   action infomation    |
//|--------------------------------------|
//|             |head      | body        |
//|--------------------------------------|



//transfer head:消息传送中的信息，如消息长度等，与请求处理的内容无关
//action logic:业务逻辑，包括两部分，逻辑头和逻辑内容
//logic head:包括诸如业务逻辑的类型（如登录验证/SQL执行等具体需要处理内容，为业务逻辑公共或大部分业务逻辑拥有的信息内容固定。各自需要记录的
//logic body:具体类型下的详细内容，如登录验证需要将用户名/密码等信息放在该部分

//logic head
//|--------------------------------------
//|logic head
//|--------------------------------------
//| action id | result | ...
//|--------------------------------------
/*
logic id:客户端请求，在服务器处理结束后原值回填
result:服务器返回结果。分为成功（SUCCESS），失败（FAIL）和带有返回信息的成功（SUCCESS WITH INFO）
info num:错误或者警告，相应的信息条数
session id:事务的id
stmt id:语句句柄id
*/

//定义最大消息长度。LSQL一次性完成数据的接受和发送，不支持在通讯中多次发送数据，所以所有发送内容都将保存在内存中，以简化程序的逻辑
#define LMSG_MAX_LENGTH (16 * 1024 * 1024)

#define LMSG_TRANSFER_HEAD_SIZE 32
#define LMSG_ACTION_HEAD_SIZE 128
#define LMSG_HEAD_SIZE (LMSG_TRANSFER_HEAD_SIZE + LMSG_ACTION_HEAD_SIZE)

#define LMSG_MAX_BODY_LENGTH (LMSG_MAX_LENGTH - LMSG_TRANSFER_HEAD_SIZE)

#define LMSG_TRANSFER_HEAD      0
#define LMSG_TRANSFER_LENGTH    LMSG_TRANSFER_HEAD
#define LMSG_TRANSFER_END       (LMSG_TRANSFER_LEN + sizeof(uint32_t))

#define LMSG_ACTION_HEAD     (0)
#define LMSG_ACTION_ID       (LMSG_ACTION_HEAD)
#define LMSG_SESSION_ID      (LMSG_ACTION_ID + LINT16_SIZE)
#define LMSG_STMT_ID         (LMSG_SESSION_ID + LINT64_SIZE)
#define LMSG_ACTION_END      (LMSG_STMT_ID + LINT64_SIZE)

//logic id
#define LMSG_ACTION_LOGIN     (1)
#define LMSG_ACTION_EXECUTION (2)
#define LMSG_ACTION_PREPARE   (3)

/* transfer head read/write*/
/*LENGTH*/
inline uint32_t lmsg_transfer_read_length(uint8_t *msg_head)
{
  uint8_t *msg = msg_head;
  return lendian_read_uint32(msg + LMSG_TRANSFER_LENGTH);
}

inline void lmsg_transfer_write_length(uint8_t *msg_head, uint32_t length)
{
  uint8_t *msg = msg_head;
  lendian_write_uint32(msg + LMSG_TRANSFER_LENGTH, length);
}

/* logic head read/write*/
/*ID 用于标识当前需要处理的逻辑*/
inline uint16_t lmsg_read_action_id(uint8_t *msg_head)
{
  uint8_t *msg = msg_head;
  return lendian_read_uint16(msg);
}

inline void lmsg_write_action_id(uint8_t *msg_head, uint16_t id)
{
  uint8_t *msg = msg_head;
  lendian_write_uint16(msg, id);
}

inline uint64_t lmsg_read_session_id(uint8_t *msg_head)
{
  uint8_t *msg = msg_head + LMSG_SESSION_ID;
  return lendian_read_uint64(msg);
}

inline void lmsg_write_session_id(uint8_t *msg_head, uint64_t session_id)
{
  uint8_t *msg = msg_head + LMSG_SESSION_ID;
  lendian_write_uint64(msg, session_id);
}

inline uint64_t lmsg_read_stmt_id(uint8_t *msg_head)
{
  uint8_t *msg = msg_head + LMSG_SESSION_ID;
  return lendian_read_uint64(msg);
}

inline void lmsg_write_stmt_id(uint8_t *msg_head, uint64_t stmt_id)
{
  uint8_t *msg = msg_head + LMSG_STMT_ID;
  lendian_write_uint64(msg, stmt_id);
}

/*
action head的内存存储结构，方便统一的写入
*/
struct lmsg_action_head_struct
{
  uint16_t action_id;
  uint8_t  result;
  uint16_t info_num;
  uint64_t session_id;
  uint64_t stmt_id;
};
typedef lmsg_action_head_struct lmsg_action_head_t;

/*
为便于利用action head的空余部分
*/
struct lmsg_head_extra_struct
{
  uint32_t extra[LMSG_ACTION_HEAD_SIZE - LMSG_ACTION_END];
};
typedef struct lmsg_head_extra_struct lmsg_head_extra_t;

//class CommPort;

#define LMSG_BUFFER_SIZE (1024 * 16)
class Message
{
private :
  uint8_t  buffer_fast_[LMSG_BUFFER_SIZE];
  uint32_t msg_length_;
  uint8_t  *buffer_;
  uint32_t buffer_size_;

  void SetBuffer(uint8_t *buffer, uint32_t buffer_size)
  {
    buffer_ = buffer;
    buffer_size_ = buffer_size;
  }

  void Reset()
  {
    msg_length_ = 0;
  }

public :
  Message()
  {
    SetBuffer(buffer_fast_, LMSG_BUFFER_SIZE);
  }

  ~Message()
  {
    if (buffer_ != buffer_fast_)
    {
      //TODO:释放分配的内存
    }
  }

  //获取action消息体的缓冲区，用于Message对象外填充消息
  uint8_t *GetActionBodyBuffer(uint32_t *buffer_size)
  {
    *buffer_size = buffer_size_;
    return buffer_ + LMSG_HEAD_SIZE;
  }

  //拼装好的消息写入消息对象
  lret WriteMsg(uint8_t *action_body, uint32_t body_len
                , lmsg_action_head_t *action_head)
  {
    /*if ((buffer_ + LMSG_HEAD_SIZE) == data_)
    {
      //TODO:使用的是对象提供的缓冲区
    }
    else
    {
      //TODO:重新分配内存
      }*/

    //写入头信息
    return LSQL_SUCCESS;
  }

  lret WriteMsg(uint8_t *action_body, uint32_t body_len
                , lmsg_action_head_t *action_head
                , lmsg_head_extra_t *extra)
  {
    WriteMsg(action_body, body_len, action_head);
    //TODO:写入extra信息
    return LSQL_SUCCESS;
  }

  //获取填写的消息
  uint8_t* GetMsg(uint32_t *body_length, lmsg_action_head_t *head)
  {
    //*msg_length = msg_length_;
    return buffer_ + LMSG_TRANSFER_HEAD_SIZE;
  }

  //接收消息
  /*lret Recieve(CommPort *port)
  {
    int r = port->Recieve(buffer_, buffer_size_);

    if (r <= 0)
      return LSQL_ERROR;

    if (r > LMSG_MAX_LENGTH)
      return LSQL_ERROR;

    if (r > buffer_size_)
    {
      //TODO:重新分配内存空间，并接收全部数据
    }

    //TODO:填写接受的信息

    return LSQL_SUCCESS;
  }

  //发送数据，在WriteMsgBuffer之后
  lret Send(CommPort *port)
  {
    int r = port->Send(buffer_, msg_length_ + LMSG_TRANSFER_HEAD_SIZE);
    return LSQL_SUCCESS;
    }*/
};

/*class NetWriteStream
{
public :
  NetWriteStream(void *buffer)
  {
  }
  ~NetStream()
  {
  }

  void Write(uint8_t *data, uint32_t len)
  {
  }

  void WriteUint8(uint8_t data)
  {
  }

  void WriteUint16(uint16_t data)
  {
  }

  //如果初始化时使用的缓冲区空间足够，则返回该缓冲区
  uint8_t* FinishWriting(uint32_t *len)
  {
    return NULL;
  }
};
*/

#endif // LSQL_INCLUDE_LMESSAGE_H_
