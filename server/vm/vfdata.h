/*
  虚拟机运行中所函数之间传递的数据
 */

#ifndef LSQL_SERVER_VM_VFDATA_H_
#define LSQL_SERVER_VM_VFDATA_H_

#include "sqltypes.h"
#include "column.h"
#include "memory.h"
#include <stdint.h>

struct vffield_struct
{
  coldef_t coldef;  //列定义
  uint16_t length;  //存储长度
  uint8_t *data;    //列数据
};
typedef struct vffield_struct vffield_t;

class VFData
{
public:
  static VFData *Create(uint16_t columns_amount, coldef_t *columns,
                        uint16_t row_array_size, Memory *memory);

public :
  uint16_t fields_amount() { return fields_amount_; }
  uint16_t filled_rows() { return filled_rows_; }

private:
  uint16_t fields_amount_;   //列数目
  uint16_t rows_array_size_; //可存储数据的数组长度
  uint16_t filled_rows_;     //实际数据的长度
  vffield_t **fields_;       //保存数据的存储空间

  VFData();
};

#endif //LSQL_SERVER_VM_VFDATA_H_
