#ifndef LSQL_SQL_COLUMN_H_
#define LSQL_SQL_COLUMN_H_

#include "lsql.h"
#include "lendian.h"
#include "ltypedef.h"
#include "sqltypes.h"
#include <vector>

using namespace std;

struct coldef_struct
{
  sqltype_def_t type_def; //sql类型定义
  bool nullable;  //列是否可为null
};
typedef struct coldef_struct coldef_t;
#define COLDEF_SIZE (sizeof(coldef_t[1]))

#define COLDEF_NET_HEAD (0)
#define COLDEF_NET_TYPE (COLDEF_NET_HEAD)
#define COLDEF_NET_PREC (COLDEF_NET_TYPE + LINT16_SIZE)
#define COLDEF_NET_SCALE (COLDEF_NET_PREC + LINT16_SIZE)
#define COLDEF_NET_NULLABLE (COLDEF_NET_SCALE + LINT16_SIZE)
#define COLDEF_NET_TAIL (COLDEF_NET_NULLABLE + LINT8_SIZE)

#define COLDEF_NET_SIZE COLDEF_NET_TAIL

/*
网络格式和结构之间的转换，n表示net
*/
/*
  return : > 0 bytes used in buffer
           = 0 error occured in writing to buffer
*/
inline uint16_t
coldef2n(coldef_t def, void *buffer, int size)
{
  if (size < COLDEF_NET_SIZE)
    return 0;

  char *buffer_inner = (char*)buffer;
  lendian_write_uint16(buffer_inner, def.type);
  buffer_inner += LINT16_SIZE;
  lendian_write_uint16(buffer_inner, def.precision);
  buffer_inner += LINT16_SIZE;
  lendian_write_uint16(buffer_inner, def.scale);
  buffer_inner += LINT16_SIZE;
  lendian_write_uint8(buffer_inner, def.nullable);
  buffer_inner += LINT8_SIZE;

  return COLDEF_NET_SIZE;
}

/*
  return : > 0 bytes read from buffer
           = 0 error occured in writing to buffer
*/
inline uint16_t
n2coldef(coldef_t *def, void *buffer)
{
  char *buffer_inner = (char*)buffer;

  def->type = lendian_read_uint16(buffer_inner);
  buffer_inner += LINT16_SIZE;
  def->precision = lendian_read_uint16(buffer_inner);
  buffer_inner += LINT16_SIZE;
  def->scale = lendian_read_uint16(buffer_inner);
  buffer_inner += LINT16_SIZE;
  def->nullable = lendian_read_uint8(buffer_inner);
  buffer_inner += LINT8_SIZE;

  return COLDEF_NET_SIZE;
}

/*
多列定义的组合，表的定义
*/
struct columns_def_struct
{
  /*增加列定义*/
  void add_coldef(coldef_t coldef)
  {
    if (sqltype_is_storage_fix(coldef.type))
    {
      uint16_t storage_size = sqltype_storage_fix_size(coldef.type);
      fix_storage_size += storage_size;
    }
    columns.push_back(coldef);
  }

  /*存储null flag所占用的空间*/
  uint16_t columns_nullflag_storage_space()
  {
    uint32_t column_number = columns.size();
    if (column_number == 0)
      return 0;
    return column_number % 8 + 1;
  }

  uint16_t columns_fix_storage_space()
  {
    uint16_t fix_columns_size = 0;
    for (int i = 0; i < columns.size(); i++)
    {
      coldef_t coldef = columns.at(i);
      fix_columns_size += sqltype_storage_fix_size(coldef.type);
    }
  }

  uint16_t fix_storage_size;
  vector<coldef_t> columns;
};
typedef struct columns_def_struct columns_def_t;

#endif //LSQL_SQL_COLUMN_H_
