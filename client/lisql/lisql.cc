#include "lpi.h"
#include "lsql.h"

lpi_henv_t env;
lpi_hdbc_t dbc;
lpi_hstmt_t stmt;

lret
lisql_connect()
{
  lpi_return_t r;
  r = lpi_alloc_env(&env);
  r = lpi_alloc_dbc(env, &dbc);
  r = lpi_set_dbc_attr(dbc, LPI_ATTR_PORT, (lpi_pointer_t)5966, 0);
  r = lpi_connect(dbc, (lpi_char_t*)"127.0.0.1", 0,
                  (lpi_char_t*)"2", 0, (lpi_char_t*)"3", 0);
}

lret
lisql_disconnect()
{
  return LSQL_SUCCESS;
}

int
main(int argc, char *argv[])
{
  lret r = LSQL_ERROR;

  r = lisql_connect();

  r = lisql_disconnect();

  return 0;
}
