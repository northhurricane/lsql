#ifndef _LSESSION_H_
#define _LSESSION_H_

#include <vector>
#include <stdint.h>

using namespace std;

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
  void *get_port() { return port_; }
  uint64_t get_id() { return id_; }
private :
  void     *port_;
  uint64_t id_;
};

class LSessionManager
{
public :
  static LSession *CreateSession(void *port);
  static void DestroySession(LSession *session);
  static LSession *FindByPort(void *port);
  static LSession *FindById(uint64_t id);
};

#endif //_LSESSION_H_
