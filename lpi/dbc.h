#ifndef LSQL_LPI_DBC_H_
#define LSQL_LPI_DBC_H_

#include "common.h"
#include "enet.h"
#include <list>

typedef char host_t[256];
typedef char user_t[128];

class Enviroment;
class Statement;

using namespace std;

class DBConnection : public HandleHead
{
private :
  uint16_t port_;
  host_t host_;
  user_t user_;
  enet_socket_t socket_;
  list<Statement*> stmt_;
  Enviroment *env_;

public :
  uint16_t port() { return port_; }
  void set_port(int16_t port) { port_ = port; }
  void set_socket(enet_socket_t socket) { socket_ = socket; }

public :
  DBConnection(Enviroment *env);
  void AddStatement(Statement *stmt);
  void RemoveStatement(Statement *stmt);
};

lpi_return_t
lpi_allocate_dbc(Enviroment *env, lpi_hdbc_t *dbc_handle);

lpi_return_t
lpi_set_dbc_attr(DBConnection *dbc, int32_t attr, int8_t *value, int32_t length);

#endif //LSQL_LPI_DBC_H_
