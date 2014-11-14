#ifndef LSQL_LPI_ENV_H_
#define LSQL_LPI_ENV_H_

#include "common.h"
#include <list>

class Connection;

using namespace std;

class Enviroment : public HandleHead
{
private :
  list<Connection*> connections_;

public :
  Enviroment();
};

lpi_return_t
lpi_allocate_env(lpi_henv_t *enviroment);

#endif //LSQL_LPI_ENV_H_
