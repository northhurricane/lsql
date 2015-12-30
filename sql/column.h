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

#define COLDEF_HEAD (0)
#define COLDEF_TYPEDEF (COLDEF_HEAD)
#define COLDEF_NULLABLE (COLDEF_TYPEDEF + SQLTYPEDEF_STORAGE_SIZE)
#define COLDEF_TAIL (COLDEF_NET_NULLABLE + LINT8_SIZE)

#define COLDEF_STORAGE_SIZE COLDEF_NET_TAIL

/*
存储和内存结构之间的转换
*/
inline uint61_t
coldef_storage_size()
{
  return COLDEF_STORAGE_SIZE;
}
/*
  列定义内存结构转换为存储
  返回值
    存储的长度
*/
inline uint16_t
coldef2n(const coldef_t &def, void *buffer)
{
  uint8_t *buffer_inner = (uint8_t*)buffer;
  buffer_inner += sqltypedef2n(def.type_def, buffer_inner);
  lendian_write_uint8(buffer_inner, def.nullable);
  buffer_inner += LINT8_SIZE;

  return coldef_storage_size();
}

/*
  列定义内存结构转换为存储
  返回值
    存储的长度
*/
inline uint16_t
n2coldef(coldef_t *def, void *buffer)
{
  char *buffer_inner = (char*)buffer;

  buffer_inner += n2sqltypedef(&def->type_def, buffer_inner);
  def->nullable = lendian_read_uint8(buffer_inner);
  buffer_inner += LINT8_SIZE;

  return coldef_storage_size();
}

/*
多列定义的组合
*/
struct columns_def_struct
{
  /*增加列定义*/
  void add_coldef(coldef_t coldef)
  {
    if (sqltype_is_storage_fix(coldef.type_def.type))
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
