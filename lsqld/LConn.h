#ifndef _LCONN_H_
#define _LCONN_H_

class LSess;

//每于客户端建立连接则创建一个LConn对象
class LConn
{
public :
  void* GetBuffer(int *buffer_size);
  void* GetBuffer(int nsize, int *buffer_size);
private :
  void *buffer;
  int size;

  LSess *lsess_;
};

#endif //_LCONN_H_
