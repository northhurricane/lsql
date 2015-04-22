/*
  虚拟机运行中所函数之间传递的数据
 */

#ifndef LSQL_SERVER_VM_VFDATA_H_
#define LSQL_SERVER_VM_VFDATA_H_

#include "lsql.h"
#include "sqltypes.h"
#include "column.h"
#include "memory.h"
#include "row.h"
#include "field.h"

struct vffield_struct
{
  coldef_t coldef;  //列定义

  field_type_t type;    //指明data的field类型
  void        *data;    //列数据。field_t或者field_ref_t类型
  uint16_t     amount;  //data数据区中的field结构的数目
};
typedef struct vffield_struct vffield_t;
#define VFFIELD_SIZE (sizeof(vffield_t[1]))

class VFData
{
public:
  static VFData *Create(uint16_t columns_amount, coldef_t *coldefs,
                        uint16_t rows_array_size, Memory *memory);
  static void Destroy(VFData *data);

public :
  uint16_t fields_amount() { return fields_amount_; }
  uint16_t filled_rows() { return filled_rows_; }

  void ClearData() { filled_rows_ = 0; }

  /*数据写入*/
  /*
    整列进行复制
    dest_fieldno：目标数据列。0-based，0表示第一列数据
    src_data：数据来源
    amount：src_data中行的数量
   */
  void FillField(uint16_t dest_fieldno, vffield_t *src_data, uint16_t amount);
  /*
    单行单列复制
    fieldno：目标数据列。0-based，0表示第一列数据
    rowno  ：目标行。0-based，0表示第一行
    type   ：列的类型
    field  ：填写的数据
   */
  void FillField(uint16_t fieldno, uint16_t rowno
                 , field_type_t type, void *field);
  /*
    单行单列复制
    fieldno：目标数据列。0-based，0表示第一列数据
    rowno  ：目标行。0-based，0表示第一行
    type   ：列的类型
    field  ：填写的数据
   */
  void FillField(uint16_t fieldno, uint16_t rowno
                 , sqltype_t type, void *data, uint16_t length);

  /*获取数据*/
  void GetField(uint16_t fieldno);
private:
  Memory *memory_;           //分配内存的内存对象
  uint16_t fields_amount_;   //列数目
  uint16_t rows_array_size_; //可存储数据的数组长度
  uint16_t filled_rows_;     //实际数据的长度
  vffield_t *fields_;        //保存数据的存储空间
  coldef_t  *coldefs_;       //列定义

  VFData();
};

#endif //LSQL_SERVER_VM_VFDATA_H_
