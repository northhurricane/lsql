#ifndef LSQL_SERVER_CONN_H
#define LSQL_SERVER_CONN_H

#include "lmutex.h"
#include "lmessage.h"
#include "lvio.h"
#include <list>

using namespace std;

class Session;

class Connection
{
private :
  Session *session_;
  Vio *vio_;
  Message message_;

public :
  Session *session() {return session_; }
  void set_session(Session *session) { session_ = session; }
  void set_vio(Vio *vio) { vio_ = vio; }
  const Message *message() { return &message_; }

  void Close()
  {
  }

  void Recieve()
  {
  }

  void Send()
  {
  }

  bool Valid()
  {
    return true;
  }
};

class ConnectionManager
{
private :
  static list<Connection*> connections_;
  static lmutex_t mutex_;
  static bool initialized_;

public :
  static void Add(Connection *connection)
  {
    lmutex_lock(&mutex_);
    connections_.push_back(connection);
    lmutex_unlock(&mutex_);
  }

  static void Remove(Connection *connection)
  {
    list<Connection*>::iterator it;
    for (it = connections_.begin(); it != connections_.end(); it)
    {
      if (*it == connection)
      {
        connections_.erase(it);
        break;
      }
    }
  }

private :
  static bool Construct();
};

#endif //LSQL_SERVER_CONN_H

