//对外接口定义。所有的对外借口都由此处定义，但真正的实现分布在各个文件中。
//如env相关的实现在env.cc文件中实现

#include "lpi.h"
#include "env.h"
#include "dbc.h"
#include "stmt.h"

extern "C" 
DllExport lpi_return_t
lpi_allocate_handle(int16_t handle_type, lpi_handle_t input_handle,
                 lpi_handle_t *output_handle)
{
  switch (handle_type)
  {
  case LPI_HANDLE_ENV:
  {
    return lpi_allocate_env(output_handle);
  }

  case LPI_HANDLE_DBC:
  {
    Enviroment *env = (Enviroment*)input_handle;
    return lpi_allocate_dbc(env, output_handle);
  }
      
  default:
    return LPI_ERROR;
  }
}

extern "C" 
lpi_return _t
lpi_set_dbc_attr(lpi_hdbc_t dbc, int32_t attr, int8_t *value, int32_t length)
{
  DBConnection *dbc2 = (DBConnection*)dbc;

  return lpi_set_dbc_attr(dbc2, attr, value, length);
}


