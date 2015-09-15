#ifndef LSQL_SQL_FIELD_H_
#define LSQL_SQL_FIELD_H_

#include <stdint.h>
#include "sqltypes.h"
/*
  列数据的内存对象
*/

#define MAX_CHAR_IN_BYTES 4097

enum field_type_enum {
  FIELD_ALL = 1,   //保存char类型数据在结构内，field_t
  FIELD_REF = 2    //保持char类型数据的
};
typedef enum field_type_enum field_type_t;

union field_fix_union
{
  uint32_t integer;     //对应LSQL_TYPE_INT类型
  uint16_t smallint;
};

/*field_fix_t放置于field_t和field_ref_t结构的第一个成员（针对C的新手），对于fix的类型，可以直接使用*/
typedef union field_fix_union field_fix_t;

/*可以容纳所有数据类型的union数据类型，char类型的数据将被保存在该结构中*/
union field_all_union
{
  field_fix_t fix;
  char chars[MAX_CHAR_IN_BYTES];
  uint16_t chars_length;
};
typedef union field_all_union field_all_t;

/*相对field_all_t结构，char类型的数据将只保存指针和长度，不进行实际数据的存储*/
union field_ref_union
{
  field_fix_t fix;
  void *chars;
  uint16_t chars_length;
};
typedef field_ref_union field_ref_t;

#define FIELD_ALL_SIZE (sizeof(field_all_t[1]))
#define FIELD_REF_SIZE (sizeof(field_ref_t[1]))

void field_set_data(field_type_t field_type, void *field
                    , sqltype_t sqltype, void *data, uint16_t length);

void field_add(
  field_type_t l_type, sqltype_t l_sqltype, void *l_field
  ,field_type_t r_type, sqltype_t r_sqltype, void *r_filed);

#endif //LSQL_SQL_FIELD_H_

