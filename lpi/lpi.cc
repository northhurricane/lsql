#include "lpi.h"
#include "env.h"

extern "C" 
DllExport lpi_return_t
lpi_allocate_handle(int16_t handle_type, lpi_handle_t input_handle,
                 lpi_handle_t *output_handle)
{
  switch (handle_type)
  {
    case LPI_HANDLE_ENV:
      return lpi_allocate_env(output_handle);
  }
  return LPI_ERROR;
}
