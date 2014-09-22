#ifndef _ENV_H
#define _ENV_H

#include "common.h"
#include "dbc.h"
#include <list>

class Connection;

using namespace std;
class Enviroment : public Head
{
public :
  list<Connection*> connections;
};

lpi_return_t
lpi_allocate_env(lpi_henv_t *enviroment);

#endif //_ENV_H
