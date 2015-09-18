#ifndef LSQL_SQL_ROW_H_
#define LSQL_SQL_ROW_H_

#include "lendian.h"
#include "column.h"
#include "sqltypes.h"

using namespace std;


/*内存中的行数据，由多个内存列构成，只保存数据。数据的元信息不在此处保存*/
/*
行分为原始行（raw row）和结构化行（struct row）
原始行以二进制格式存储数据，其结构如下描述
结构化行通过结构和数据类型存储数据
*/
/*lsql的原始行布局（raw row layout）*/
/*
row length/nullflag/fix length fields/variable length fields
row length:2字节长，行的长度
nullflag:每个列占用一个位，0表示null，1表示not null
fix length fields:定常数据的存储空间
variable length fields:变长数据的存储空间。由2字节长度和实际数据构成

例如 
create table t1(f1 int, f2 varchar(10));
insert into t1 values (1,'123');
所对应的为
row length:
nullflag:占用1个字节，保存f1和f2的是否为空标识
fix lenght fields:占用4个字节，保存f1的数据
variable length fields:占用5个字节，2字节为长度，3字节为数据内容
*/

#define NULL_FLAG     (0)
#define NOT_NULL_FLAG (1)


typedef void *row_raw_t;

inline bool
is_null(uint8_t flag)
{
  return flag == NULL_FLAG;
}

inline uint16_t
row_read_length(row_raw_t row)
{
  return lendian_read_uint16(row);
}

inline void
row_write_length(row_raw_t row, uint16_t length)
{
  lendian_write_uint16(row, length);
}

/*field在row中的信息*/
struct row_field_struct
{
  bool is_null_;     //列是否为null
  uint16_t offset_;  //在行中的偏移

  void set_is_null(bool is_null) {is_null_ = is_null;}
  bool is_null() { return is_null_; }

  void set_offset(uint16_t offset) { offset_ = offset; }
  uint16_t offset() { return offset_; }
};
typedef struct row_field_struct row_field_t;

/*该结构中保存所有数据内容，字符数据将保存在field结构中*/
struct row_fields_struct
{
  vector<row_field_t> fields; //列信息
};
typedef struct row_fields_struct row_fields_t;

/*
  从原始行数据中读取各列的信息，如数据是否为null，如果不为null，数据所在偏移
  return : > 0 bytes read from row.
           = 0 error occured when read from row
*/
inline uint16_t
row_fields_from_raw(row_raw_t row
                    , row_fields_t *fields, columns_def_t *colsdef)
{
  uint16_t columns_number = colsdef->columns.size();
  uint16_t fix_offset = 0;  //固定长度列数据的偏移
  uint16_t var_offset = 0;  //变长数据列的偏移
  uint16_t fix_len;  //固定列数据长度
  uint16_t var_len;  //变长列数据长度
  uint8_t  null_flag = NULL_FLAG;
  row_field_t field;
  uint8_t *buffer = (uint8_t*)row;

  //固定长度数据的空间
  fix_offset += colsdef->columns_nullflag_storage_space() + LINT16_SIZE;
  
  for (int i =0; i < columns_number; i++)
  {
    coldef_t coldef = colsdef->columns.at(i);

    field.set_is_null(false);
    field.set_offset(0);

    //read null flag
    if (is_null(null_flag))
    {
      field.set_is_null(true);
    }
    else
    {
      //read data
      if (sqltype_is_storage_fix(coldef.type))
      {
        //在定长区域寻找数据
        field.set_offset(fix_offset);
        fix_len = sqltype_storage_fix_size(coldef.type);
        fix_offset += fix_len;
      }
      else
      {
        //在变长区域寻找数据
        field.set_offset(var_offset);
        var_len = lendian_read_uint16(buffer + var_offset);
        var_offset += LINT16_SIZE;
        var_offset += var_len;
      }
    }
  }
}

//结构化行
struct row_structed_struct
{
  field_t *fields_ptr[]; //字段数组，
  uint8_t *fields; //字段的存储空间
};
typedef struct row_structed_struct row_structed_t;

struct row_structed_batch_struct
{
  uint16_t fields_number;
  uint16_t batch_number;
};

#endif //LSQL_SQL_ROW_H_

