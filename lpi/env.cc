#include "lpi.h"
#include "env.h"

#define ENVIROMENT_MAGIC_NUMBER 0x4893cb2da981cf00
Enviroment::Enviroment()
{
  magic_ = ENVIROMENT_MAGIC_NUMBER;
}

lpi_return_t
lpi_allocate_env(lpi_henv_t *enviroment)
{
  Enviroment *env = new Enviroment();

  *enviroment = env;

  return LPI_SUCCESS;
}
