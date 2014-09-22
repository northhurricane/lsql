#include "dbc.h"

lpi_return_t
lpi_allocate_dbc(lpi_henv_t enviroment_handle, lpi_hdbc_t *dbc_handle)
{
  return LPI_ERROR;
}

DllExport extern "C" lpi_return_t
lpi_connect(lpi_hdbc_t connection_handle,
            uint8_t *server, uint32_t server_length,
            uint8_t *user_name, uint32_t user_name_length,
            uint8_t *pass_word, uint32_t pass_word_length)
{
  Connection *dbc = (Connection*)connection_handle;

  int r = enet_client_create(&dbc->client, dbc->host, dbc->port);
  if (r < 0)
    return LPI_ERROR;

  return LPI_SUCCESS;
}

DllExport extern "C" lpi_return_t 
lpi_disconnect(lpi_hdbc_t connection_handle)
{
  Connection *dbc = (Connection*)connection_handle;
  return LPI_SUCCESS;
}
