#ifndef LSQL_SERVER_STMT_H_
#define LSQL_SERVER_STMT_H_

class Session;

class Statement
{
private:
  Session *session_;

public:
  Session *session() {return session_;}
};

#endif //LSQL_SERVER_STMT_H_

