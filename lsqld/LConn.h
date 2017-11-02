#ifndef _LCONN_H_
#define _LCONN_H_

#include <map>

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
