#ifndef _LCONN_H_
#define _LCONN_H_

#include <map>

class LSess;
class LConnManager;

//每于客户端建立连接则创建一个LConn对象
class LConn
{
public :
  void* GetBuffer()
  {
    return buffer_;
  }
  int GetBufferSize()
  {
    return size_;
  }
  void* GetBuffer(int nsize)
  {
    if (size_ > nsize)
      return buffer_;

    size_ = nsize;
    return buffer_;
  }
  void SetMsgLen(int len)
  {
    msg_len_ = len;
  }

  friend class LConnManager;
private :
  void *buffer_;
  int size_;
  int msg_len_;

  LSess *sess_;

protected :
  LConn(int size);
};

using namespace std;

class LConnManager
{
public :
  static LConn* CreateConn();
  static void DestroyConn(LConn *conn);
private:
  typedef map<LConn*, LConn*> conn_map_t;
  typedef conn_map_t::iterator conn_map_it_t;
  static conn_map_t conn_map;
};

#endif //_LCONN_H_
