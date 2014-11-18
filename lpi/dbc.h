#ifndef LSQL_LPI_DBC_H_
#define LSQL_LPI_DBC_H_

#include "common.h"
#include "enet.h"
#include "lmessage.h"
#include "lpi.h"
#include <list>

typedef char host_t[256];
typedef char user_t[128];

class Enviroment;
class Statement;
class Vio;

using namespace std;

class DBConnection : public HandleHead
{
private :
  uint16_t port_;
  host_t host_;
  user_t user_;
  list<Statement*> stmt_;
  Enviroment *env_;
  Vio *vio_;
  Message message_;

public :
  uint16_t port() { return port_; }
  void set_port(uint16_t port) { port_ = port; }
  Vio *vio() { return vio_; }
  void set_vio(Vio *vio) { vio_ = vio; }

public :
  DBConnection(Enviroment *env);
  void AddStatement(Statement *stmt);
  void RemoveStatement(Statement *stmt);

  Message *GetMessage() { return &message_; }
  lret Send();
  lret Reciev(); 
};

lpi_return_t
lpi_allocate_dbc(Enviroment *env, lpi_hdbc_t *dbc_handle);

lpi_return_t
lpi_dbc_connect(DBConnection *dbc,
            uint8_t *host, int32_t host_len,
            uint8_t *user, int32_t user_len,
            uint8_t *password, int32_t password_len);

lpi_return_t
lpi_set_dbc_attr(DBConnection *dbc, int32_t attr, lpi_pointer_t value, int32_t length);

#endif //LSQL_LPI_DBC_H_
