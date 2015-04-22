#ifndef LSQL_SQL_ROW_H_
#define LSQL_SQL_ROW_H_

#include "field.h"

/*内存中的行数据，由多个内存列构成，只保存数据。数据的元信息不在此处保存*/

/*该结构中保存所有数据内容，字符数据将保存在field结构中*/
struct row_struct
{
  uint16_t amount;  //列数目
  field_t *fields;  //数据列
};
typedef struct row_struct row_t;

/*字符数据不进行保存，只有指向字符数据的指针。对于没有字符数据或者字符数据固定的情况，减少空间使用*/
struct row_ref_struct
{
  uint16_t amount;      //列数目
  field_ref_t *fields;  //列数据
};
typedef struct row_ref_struct row_ref_t;

#endif //LSQL_SQL_ROW_H_

