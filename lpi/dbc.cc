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
lpi_set_dbc_attr(DBConnection *dbc, int32_t attr, lpi_pointer_t value, int32_t length)
{
  switch (attr)
  {
  case LPI_ATTR_PORT:
    uint16_t port = ((uint64_t)value);
    dbc->set_port(port);
    break;
  }
  return LPI_SUCCESS;
}

lpi_return_t
lpi_dbc_connect(DBConnection *dbc,
            lpi_char_t *host, int32_t host_len,
            lpi_char_t *user, int32_t user_len,
            lpi_char_t *password, int32_t password_len)
{
  enet_socket_t socket;
  /*  char host_inner[256];

  if (host_len >= sizeof(host_inner))
  {
    strncpy(host_inner, host, sizeof(host_inner));
  }
  else
  {
    strncpy(host_inner, host, host_len);
    }*/

  //建立连接
  int r = enet_client_create(&socket, (const char*)host, dbc->port());
  Vio *vio = new VioEnet(socket);
  dbc->set_vio(vio);

  //登录验证
  lmessage_login_request_t request;
  request.version = 0;
  request.user = (uint8_t*)user;
  request.user_length = user_len;
  request.password = (uint8_t*)password;
  request.password_length = password_len;

  Message *message = dbc->GetMessage();
  lret ret = lmessage_login_request_write(message, &request);
  message->Send(vio);

  return LPI_SUCCESS;
}

lpi_return_t 
lpi_disconnect(DBConnection *dbc)
{
  return LPI_SUCCESS;
}
