#ifndef _SESS_H
#define _SESS_H

class Connection;

class Session
{
public :
  Connection *connection;
};

class SessionManager
{
public :
  static Session *CreateSession(Connection *connectino);
};

#endif //_SESS_H
