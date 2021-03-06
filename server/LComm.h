#ifndef _LCOMM_H_
#define _LCOMM_H_

class LComm;
class LPort;

LComm* lcomm_get();

enum lcomm_event_type_enum
{
  LCOMM_EVENT_CONNECT,
  LCOMM_EVENT_MESSAGE,
  LCOMM_EVENT_DISCONNECT,
};
typedef lcomm_event_type_enum lcomm_event_type_e;

struct lcomm_event_struct
{
  LPort *port;
  lcomm_event_type_e type;

  lcomm_event_type_e get_type() { return type; }
  void set_type(lcomm_event_type_e type_) { type = type_; }
  LPort *get_port() { return port; }
  void set_port(LPort *port_) { port = port_; }
};
typedef lcomm_event_struct lcomm_event_t;

#define LCOMM_MAX_EVENT_WAIT    (64)

/*
服务器与客户端通讯的抽象。
单例，每个服务器只有一个
*/
class LComm
{
public :
  static int Initialize();
  static int Deinitialize();
public :
  /*
    等待事件发生
    参数  ：
      events:输出参数，事件数组
      size  :
    返回值：
      -1   : 发生错误
      正数 : 事件个数
    说明：
      当事件的类型为LCOMM_EVENT_CONNECT，event的port为建立好连接的对象。
  */
  int Wait(lcomm_event_t *events, int size);
  /*
    关闭通信，此时不接收任何连接或者信息
  */
  int Close();
  /**/
  bool Closed() { return closed_; }

private :
  bool closed_;
};

#endif //_LCOMM_H_
