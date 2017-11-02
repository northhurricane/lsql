#ifndef _LPORT_H_
#define _LPORT_H_

//用于建立连接的端口对象，每个lsqld服务实例允许期间只有一个改对象的
class LPort
{
public :
  enum Type {
    Invalid,
    Socket,
  };
  static int Init();
  static int Deinit();

private :
  void *port;
};

#endif //_LPORT_H_

