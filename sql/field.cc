#include "lsql.h"
#include "field.h"
#include <string.h>

void field_set_data(field_type_t field_type, void *field
                    , sqltype_t sqltype, void *data, uint16_t length)
{
  
  switch (sqltype)
  {
  case LSQL_TYPE_INT:
  {
    int32_t *pval = (int32_t*)data;
    int32_t v = *pval;
    field_fix_t *fix = (field_fix_t*)field;
    fix->integer = v;
    break;
  }
  case LSQL_TYPE_VARCHAR:
  {
    if (field_type == FIELD_ALL)
    {
      field_t *field_all = (field_t*)field;
      memcpy(field_all->chars, data, length);
      field_all->chars_length = length;
    }
    else
    {
      lassert(field_type = FIELD_REF);
      field_ref_t *field_ref = (field_ref_t*)field;
      field_ref->chars = data;
      field_ref->chars_length = length;
    }
  }

  default:
    lassert(false);
  }
}
