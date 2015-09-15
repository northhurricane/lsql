#ifndef LSQL_SQL_COLUMN_H_
#define LSQL_SQL_COLUMN_H_

#include "lsql.h"
#include "lendian.h"

using namespace std;

struct coldef_struct
{
  uint16_t type;  //SQL的类型
  uint16_t precision; //对char类型来说就是定义的长度
  uint16_t scale;     //和precision配合使用，说明精度。比如decimal(10,2)，precision为10，scale为2。参考sql的标准定义
  bool     nullable;  //列是否可为null
};
typedef struct coldef_struct coldef_t;
#define COLDEF_SIZE (sizeof(coldef_t[1]))

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
  char *buffer_inner = (char*)buffer;
  return 0;
}

/*
  return : > 0 bytes read from buffer
           = 0 error occured in writing to buffer
*/
inline uint16_t
n2coldef(coldef_t *def, void *buffer)
{
  return 0;
}

/*
多列定义的组合，表的定义
*/
struct columns_def_struct
{
  void add_coldef(coldef_t coldef)
  {
    if (sqltype_is_storage_fix(coldef.type))
    {
      uint16_t storage_size = 0;
      fix_storage_size += storage_size;
    }
    columns.push_back(coldef);
  }

  uint16_t fix_storage_size; //固定长度字段所占的存储空间
  vector<coldef_t> columns;
};
typedef struct columns_def_struct columns_def_t;

#endif //LSQL_SQL_COLUMN_H_
