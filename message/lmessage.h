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
*/

//定义最大消息长度。LSQL一次性完成数据的接受和发送，不支持在通讯中多次发送数据，所以所有发送内容都将保存在内存中，以简化程序的逻辑
#define LMSG_MAX_LENGTH (16 * 1024 * 1024)

#define LMSG_TRANSFER_HEAD_SIZE 32
#define LMSG_ACTION_HEAD_SIZE 128
#define LMSG_HEAD_SIZE (LMSG_TRANSFER_HEAD_SIZE + LMSG_ACTION_HEAD_SIZE)

#define LMSG_TRANSFER_HEAD      0
#define LMSG_TRANSFER_LENGTH    LMSG_TRANSFER_HEAD
#define LMSG_TRANSFER_END       (LMSG_TRANSFER_LENGTH + LINT32_SIZE)

#define LMSG_ACTION_HEAD     (0)
#define LMSG_ACTION_ID       (LMSG_ACTION_HEAD)
#define LMSG_RESULT          (LMSG_STMT_ID + LINT16_SIZE)
#define LMSG_RESULT_INFO_NUM (LMSG_RESULT + LINT8_SIZE)
#define LMSG_ACTION_END      (LMSG_RESULT_INFO_NUM + LINT16_SIZE)

//action id
#define LMSG_ACTION_LOGIN      (1)
#define LMSG_ACTION_ALLOC_STMT (2)
#define LMSG_ACTION_EXECUTION  (3)
#define LMSG_ACTION_PREPARE    (4)

#endif // LSQL_INCLUDE_LMESSAGE_H_
