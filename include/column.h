#ifndef LSQL_INCLUDE_COLUMN_H_
#define LSQL_INCLUDE_COLUMN_H_

#include <stdint.h>
#include "lendian.h"

struct coldef_struct
{
  uint16_t type;  //SQL的类型
  uint16_t precision; //对char类型来说就是定义的长度
  uint16_t scale;     //和precision配合使用，说明精度。比如decimal(10,2)，precision为10，scale为2
  bool     nullable;  //列是否可为null
};
typedef struct coldef_struct coldef_t;

/*
  return : > 0 bytes used in buffer .
           = 0 error occured in writing to buffer
*/
inline uint16_t
coldef2n(coldef_t def, void *buffer, int size)
{
  char *buffer_inner = (char*)buffer;
  return 0;
}

inline void
n2coldef(coldef_t *def, void *buffer)
{
}

struct coldef_array_struct
{
  uint16_t col_num;
  coldef_t *coldefs;
};
typedef struct coldef_array_struct coldef_array_t;


typedef std::list<coldef_t> ListColdef;


#endif //LSQL_INCLUDE_COLUMN_H_
