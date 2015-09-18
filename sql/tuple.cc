#include "tuple.h"

tuple_t*
tuple_create(
  columns_def_t *columns_def
)
{
  tuple_t *tuple = NULL;
  tuple->memory = NULL;

  return tuple;
}

tuple_t*
