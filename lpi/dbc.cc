#include "dbc.h"
#include "env.h"
#include "lmessage_login.h"

DBConnection::DBConnection(Enviroment *env)
{
  env_ = env;
}

lpi_return_t
lpi_allocate_dbc(Enviroment *env, lpi_hdbc_t *dbc_handle)
{
  DBConnection *dbc = new DBConnection(env);

  *dbc_handle = dbc;

  return LPI_SUCCESS;
}

lpi_return_t
lpi_set_dbc_attr(DBConnection *dbc, int32_t attr, int8_t *value, int32_t length)
{
  switch (attr)
  {
  case LPI_ATTR_PORT:
    uint16_t port = *((uint16_t*)value);
    dbc->set_port(port);
    break;
  }
  return LPI_SUCCESS;
}

lpi_return_t
lpi_dbc_connect(DBConnection *dbc,
            uint8_t *host, int32_t host_len,
            uint8_t *user, int32_t user_len,
            uint8_t *password, int32_t password_len)
{
  enet_socket_t socket;
  char host_inner[256];

  //建立连接
  int r = enet_client_create(&socket, host_inner, dbc->port());
  dbc->set_socket(socket);

  //登录验证
  lmessage_login_request_t request;
  request.version = 0;
  request.user = (uint8_t*)user;
  request.user_length = user_len;
  request.password = (uint8_t*)password;
  request.password_length = password_len;

  lret ret = lmessage_login_request_write(dbc->GetMessage(), &request);

  return LPI_SUCCESS;
}

lpi_return_t 
lpi_disconnect(DBConnection *dbc)
{
  return LPI_SUCCESS;
}
