#ifndef _LPORT_H_
#define _LPORT_H_

/*
通信端口对象，消息通过端口进行发送接受
*/
class LPort
{
public :
  int Recieve();
  int Send();
};

#endif //_LPORT_H_
