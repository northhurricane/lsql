#ifndef _LSESSION_H_
#define _LSESSION_H_

#include <stdint.h>
#include <map>

using namespace std;

class LPort;
class LStmt;

typedef map<uint64_t, LStmt*> stmt_id_map_t;
typedef stmt_id_map_t::iterator stmt_id_map_it_t;

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
  LStmt *FindStmt(uint64_t id)
  {
    stmt_id_map_it_t it = stmt_id_map_.find(id);
  }

private :
  LPort    *port_;
  uint64_t id_;

  /*在该会话上分配的语句句柄的map*/
  stmt_id_map_t stmt_id_map_;
};

LSession *session_create(LPort *port);
void session_destroy(LSession *session);
LSession *session_find_by_port(LPort *port);
LSession *session_find_by_id(uint64_t id);

#endif //_LSESSION_H_
