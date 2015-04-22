#include "vfdata.h"
#include <string.h>

VFData*
VFData::Create(uint16_t columns_amount, coldef_t *coldefs,
               uint16_t rows_array_size, Memory *memory)
{
  VFData *vfdata = new VFData();
  //分配指向各列的数组空间
  uint32_t size = 0;
  size = columns_amount * VFFIELD_SIZE;
  vfdata->fields_ = (vffield_t*)memory->Allocate(size);

  //分配coldef_t的存储空间
  size = columns_amount * COLDEF_SIZE;
  vfdata->coldefs_ = (coldef_t*)memory->Allocate(size);
  memcpy(vfdata->coldefs_, coldefs, size);

  //分配各个vffield的存储空间
  for (int i = 0; i < columns_amount; i++)
  {
    coldef_t *coldef = coldefs + i;
    vffield_t *vffield = vfdata->fields_ + i;
    size = 0;
    bool use_ref_field = type_is_fix_storage_lenght(coldef->type);
    if (use_ref_field)
    {
      size = FIELD_REF_SIZE * rows_array_size;
    }
    else
    {
      size = FIELD_ALL_SIZE *rows_array_size;
    }

    vffield->data = memory->Allocate(size);
  }
  vfdata->memory_ = memory;
  vfdata->fields_amount_ = columns_amount;
  vfdata->rows_array_size_ = rows_array_size;

  return vfdata;
}

void
VFData::Destroy(VFData *data)
{
  delete data;

  return;
}

VFData::VFData()
{
  memory_ = NULL;
  fields_amount_ = 0;
  rows_array_size_ = 0;
  filled_rows_ = 0;
  fields_ = NULL;
  coldefs_ = NULL;
}

void
VFData::FillField(uint16_t dest_fieldno, vffield_t *src_data, uint16_t amount)
{
}

void
VFData::FillField(uint16_t fieldno, uint16_t rowno
                  , field_type_t type, void *field)
{
}

void
VFData::FillField(uint16_t fieldno, uint16_t rowno
                  , sqltype_t type, void *data, uint16_t length)
{
  //获取field
  vffield_t *vffield = fields_ + fieldno;

  //获取行数据的位置
  lassert(rowno < vffield->amount);
  void *prow = NULL;
  if (vffield->type == FIELD_REF)
  {
    prow = ((uint8_t*)vffield->data) + FIELD_REF_SIZE * rowno;
  }
  else
  {
    prow = ((uint8_t*)vffield->data) + FIELD_ALL_SIZE * rowno;
  }

  field_set_data(vffield->type, prow, type, data, length);
  //进行数据填写
}

