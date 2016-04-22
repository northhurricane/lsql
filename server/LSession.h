#ifndef _LSESSION_H_
#define _LSESSION_H_

#include <vector>
#include <stdint.h>

using namespace std;

class LPort;

/*
  会话对象
*/
class LSession
{
public :
  /*
    取消会话上的操作，诸如SQL执行等操作
  */
  int Cancel();
  /*
    关闭会话。释放会话资源，此时端口必须为断开状态，
  */
  int Close();
  /**/
  LPort *get_port() { return port_; }
  uint64_t get_id() { return id_; }

private :
  
  LPort    *port_;
  uint64_t id_;
};

LSession *session_create(LPort *port);
void session_destroy(LSession *session);
LSession *session_find_by_port(LPort *port);
LSession *session_find_by_id(uint64_t id);

#endif //_LSESSION_H_
