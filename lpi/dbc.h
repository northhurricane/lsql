#ifndef _DBC_H
#define _DBC_H

#include "common.h"
#include "enet.h"
#include <list>

typedef char host_t[256];
typedef char user_t[128];

class Enviroment;
class Statement;

using namespace std;

class Connection : public Head
{
public :
  uint16_t port;
  host_t host;
  user_t user;
  enet_client_t client;
  list<Statement*> statements;
  Enviroment *enviroment;
};

lpi_return_t
lpi_allocate_dbc(lpi_henv_t enviroment_handle, lpi_hdbc_t *dbc_handle);

#endif //_DBC_H
