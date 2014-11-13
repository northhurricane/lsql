#ifndef LSQL_SERVER_CONN_H
#define LSQL_SERVER_CONN_H

#include "enet.h"
#include "lmutex.h"
#include "lmessage.h"
#include <list>

using namespace std;

class Session;

class Connection
{
private :
  Session *session_;
  enet_socket_t socket_;
  Message message_;

public :
  Session *session() {return session_; }
  void set_session(Session *session) { session_ = session; }
  enet_socket_t socket() {return socket_;}
  void set_socket(enet_socket_t socket) { socket_ = socket;}
  const Message *message() { return &message_; }

  void Recieve()
  {
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

