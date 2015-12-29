#ifndef LSQL_INCLUDE_SQLTYPE_H_
#define LSQL_INCLUDE_SQLTYPE_H_

#include "ltypedef.h"
#include "lendian.h"

/*
  类型，如varchar，int等
*/
typedef int16_t sqltype_t;

/*
  在sql命令中声明的数据类型，如varchar(10), decimal(10,4)等
*/
struct sqltypedef_struct
{
  sqltype_t type;    //类型
  uint16_t  prec;    //精度。对char类型来说就是定义的长度
  uint16_t  scale;   //刻度。和prec配合使用，说明精度。比如decimal(10,2)，precision为10，scale为2。参考sql的标准定义
};
typedef struct sqltypedef_struct sqltypedef_t

#define SQL_TYPE_INVALID   (0)
#define SQL_TYPE_INT       (1)   //4字节长度整形
#define SQL_TYPE_CHAR      (2)   //定长字符类型，内部存储为变长
#define SQL_TYPE_VARCHAR   (3)   //变长字符类型
#define SQL_TYPE_SMALLINT  (4)
#define SQL_TYPE_TINYINT   (5)
#define SQL_TYPE_BIGINT    (6)
#define SQL_TYPE_DATE      (7)
#define SQL_TYPE_TIME      (8)
#define SQL_TYPE_DATETIME  (9)

#define SQL_TYPE_INT_STORAGE_SIZE (LINT32_SIZE)

#define SQL_TYPE_INT_PREC  10
#define SQL_TYPE_INT_SCALE 0

#define SIGNED_DEF   (0)
#define UNSIGNED_DEF (1)

/*定义sqltype_def_t的存储情况*/
#define SQLTYPEDEF_HEAD (0)
#define SQLTYPEDEF_TYPE (TYPEDEF_HEAD)
#define SQLTYPEDEF_PREC (TYPEDEF_TYPE + LINT16_SIZE)
#define SQLTYPEDEF_SCALE (TYPEDEF_PREC + LINT16_SIZE)
#define SQLTYPEDEF_TAIL (TYPEDEF_SCALE + LINT16_SIZE)
#define SQLTYPEDEF_STORAGE_SIZE TYPEDEF_TAIL

inline uint16_t sqltypedef_storage_size()
{
  return SQLTYPEDEF_STORAGE_SIZE;
}

/*
  将sqltype_def_t结构以网络传输格式向缓冲区写入
  返回值：使用缓冲区的字节数
*/
inline uint16_t sqltypedef2n(sqltypedef_t def, void *buffer)
{
  uint8_t *buffer_inner = (uint8_t*)buffer;

  lendian_write_uint16(buffer_inner, def.type);
  buffer_inner += LINT16_SIZE;
  lendian_write_uint16(buffer_inner, def.prec);
  buffer_inner += LINT16_SIZE;
  lendian_write_uint16(buffer_inner, def.scale);
  buffer_inner += LINT16_SIZE;

  return sqltypedef_storage_size();
}
/*
  将sqltype_def_t结构以网络传输格式从缓冲区读取
  返回值：使用缓冲区的字节数
*/
inline uint16_t n2sqltypedef(sqltypedef_t *def, void *buffer)
{
  uint8_t *buffer_inner = (uint8_t*)buffer;

  def->type = lendian_read_uint16(buffer_inner);
  buffer_inner += LINT16_SIZE;
  def->precision = lendian_read_uint16(buffer_inner);
  buffer_inner += LINT16_SIZE;
  def->scale = lendian_read_uint16(buffer_inner);
  buffer_inner += LINT16_SIZE;

  return sqltypedef_storage_size();
}

//是否为定常数据类型
inline bool sqltype_is_storage_fix(sqltype_t type)
{
  switch (type)
  {
  case LSQL_TYPE_INT:
    return true;

  case LSQL_TYPE_VARCHAR:
  case LSQL_TYPE_CHAR:
    return false;

  defaults :
    //所以类型都应该有明确的结果
    //lsql_assert(false);
    return false;
  }
}

inline uint16_t sqltype_storage_fix_size(sqltype_t type)
{
  switch (type)
  {
  case LSQL_TYPE_INT:
    return LINT32_SIZE;

  defaults :
    //其他非固定存储的类型为0
    return 0;
  }
}


#endif //LSQL_INCLUDE_SQLTYPE_H_
